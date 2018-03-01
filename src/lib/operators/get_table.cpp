#include "get_table.hpp"

#include <optional>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_set>

#include "storage/storage_manager.hpp"
#include "types.hpp"

namespace opossum {

GetTable::GetTable(const std::string& name) : _name(name) {}

const std::string GetTable::name() const { return "GetTable"; }

const std::string GetTable::description(DescriptionMode description_mode) const {
  const auto separator = description_mode == DescriptionMode::MultiLine ? "\n" : " ";
  std::stringstream ss;
  ss << name() << separator << "(" << table_name() << ")";
  if (_excluded_chunks) {
    ss << separator << "(" << _excluded_chunks->size() << " Chunks pruned)";
  }
  return ss.str();
}

const std::string& GetTable::table_name() const { return _name; }

std::shared_ptr<AbstractOperator> GetTable::recreate(const std::vector<AllParameterVariant>& args) const {
  return std::make_shared<GetTable>(_name);
}

std::shared_ptr<const Table> GetTable::_on_execute() {
  auto original_table = StorageManager::get().get_table(_name);
  if (!_excluded_chunks || _excluded_chunks->empty()) {
    return original_table;
  }

  // we create a copy of the original table and don't include the excluded chunks
  auto pruned_table = Table::create_with_layout_from(original_table, original_table->max_chunk_size());
  auto excluded_chunks_set = std::unordered_set<ChunkID>(_excluded_chunks->cbegin(), _excluded_chunks->cend());
  for (ChunkID chunk_id{0}; chunk_id < original_table->chunk_count(); ++chunk_id) {
    if (excluded_chunks_set.count(chunk_id)) {
      continue;
    }
    pruned_table->emplace_chunk(original_table->get_chunk(chunk_id));
  }
  return pruned_table;
}

void GetTable::set_excluded_chunks(const std::vector<ChunkID>& excluded_chunks) {
  _excluded_chunks.emplace(excluded_chunks);
}
}  // namespace opossum
