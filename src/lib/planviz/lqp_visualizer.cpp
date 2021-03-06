#include "lqp_visualizer.hpp"

#include <boost/algorithm/string.hpp>
#include <iomanip>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace opossum {

LQPVisualizer::LQPVisualizer() : AbstractVisualizer() {
  // Set defaults for this visualizer
  _default_vertex.shape = "parallelogram";
}

LQPVisualizer::LQPVisualizer(GraphvizConfig graphviz_config, VizGraphInfo graph_info, VizVertexInfo vertex_info,
                             VizEdgeInfo edge_info)
    : AbstractVisualizer(std::move(graphviz_config), std::move(graph_info), std::move(vertex_info),
                         std::move(edge_info)) {}

void LQPVisualizer::_build_graph(const std::vector<std::shared_ptr<AbstractLQPNode>>& lqp_roots) {
  for (const auto& root : lqp_roots) {
    _add_vertex(root, root->description());
    _build_subtree(root);
  }
}

void LQPVisualizer::_build_subtree(const std::shared_ptr<AbstractLQPNode>& node) {
  if (node->left_input()) {
    auto left_input = node->left_input();
    _add_vertex(left_input, left_input->description());
    _build_dataflow(left_input, node);
    _build_subtree(left_input);
  }

  if (node->right_input()) {
    auto right_input = node->right_input();
    _add_vertex(right_input, right_input->description());
    _build_dataflow(right_input, node);
    _build_subtree(right_input);
  }
}

void LQPVisualizer::_build_dataflow(const std::shared_ptr<AbstractLQPNode>& from,
                                    const std::shared_ptr<AbstractLQPNode>& to) {
  float row_count, row_percentage = 100.0f;
  double pen_width;

  try {
    row_count = from->get_statistics()->row_count();
    pen_width = std::fmax(1, std::ceil(std::log10(row_count) / 2));
  } catch (...) {
    // statistics don't exist for this edge
    row_count = NAN;
    pen_width = 1.0;
  }

  if (from->left_input()) {
    try {
      float input_count = from->left_input()->get_statistics()->row_count();
      if (from->right_input()) {
        input_count *= from->right_input()->get_statistics()->row_count();
      }
      row_percentage = 100 * row_count / input_count;
    } catch (...) {
      // Couldn't create statistics. Using default value of 100%
    }
  }

  std::ostringstream label_stream;
  if (!isnan(row_count)) {
    label_stream << " " << std::fixed << std::setprecision(1) << row_count << " row(s) | " << row_percentage
                 << "% estd.";
  } else {
    label_stream << "no est.";
  }

  VizEdgeInfo info = _default_edge;
  info.label = label_stream.str();
  info.pen_width = pen_width;

  _add_edge(from, to, info);
}

}  // namespace opossum
