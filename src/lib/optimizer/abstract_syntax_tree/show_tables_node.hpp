#pragma once

#include <memory>
#include <string>

#include "optimizer/abstract_syntax_tree/abstract_non_optimizable_ast_node.hpp"

namespace opossum {

/**
 * This node type represents the SHOW TABLES management command.
 */
class ShowTablesNode : public AbstractNonOptimizableASTNode {
 public:
  ShowTablesNode();

  std::string description() const override;

  std::shared_ptr<AbstractASTNode> clone_subtree() const override;
};

}  // namespace opossum
