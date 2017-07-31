#include "constant_mappings.hpp"

#include <string>
#include <unordered_map>

namespace opossum {

const std::unordered_map<std::string, proto::ScanType> string_to_proto_scan_type = {
    {"=", proto::ScanType::OpEquals},        {"!=", proto::ScanType::OpNotEquals},
    {"<", proto::ScanType::OpLessThan},      {"<=", proto::ScanType::OpLessThanEquals},
    {">", proto::ScanType::OpGreaterThan},   {">=", proto::ScanType::OpGreaterThanEquals},
    {"BETWEEN", proto::ScanType::OpBetween}, {"LIKE", proto::ScanType::OpLike},
};

const std::unordered_map<std::string, ScanType> string_to_scan_type = {
    {"=", ScanType::OpEquals},          {"!=", ScanType::OpNotEquals},  {"<", ScanType::OpLessThan},
    {"<=", ScanType::OpLessThanEquals}, {">", ScanType::OpGreaterThan}, {">=", ScanType::OpGreaterThanEquals},
    {"BETWEEN", ScanType::OpBetween},   {"LIKE", ScanType::OpLike},
};

const std::unordered_map<ScanType, std::string> scan_type_to_string = {
    {ScanType::OpEquals, "="},          {ScanType::OpNotEquals, "!="},  {ScanType::OpLessThan, "<"},
    {ScanType::OpLessThanEquals, "<="}, {ScanType::OpGreaterThan, ">"}, {ScanType::OpGreaterThanEquals, ">="},
    {ScanType::OpBetween, "BETWEEN"},   {ScanType::OpLike, "LIKE"},
};

const std::unordered_map<const JoinMode, std::string> join_mode_to_string = {
    {JoinMode::Cross, "Cross"}, {JoinMode::Inner, "Inner"}, {JoinMode::Left, "Left"}, {JoinMode::Natural, "Natural"},
    {JoinMode::Outer, "Outer"}, {JoinMode::Right, "Right"}, {JoinMode::Self, "Self"},
};

const std::unordered_map<const ExpressionType, std::string> expression_type_to_string = {
    {ExpressionType::Literal, "Literal"},
    {ExpressionType::Star, "Star"},
    {ExpressionType::Parameter, "Parameter"},
    {ExpressionType::ColumnReference, "ColumnReference"},
    {ExpressionType::FunctionReference, "FunctionReference"},
    {ExpressionType::Operator, "Operator"},
    {ExpressionType::Select, "Select"},
    {ExpressionType::Plus, "Plus"},
    {ExpressionType::Minus, "Minus"},
    {ExpressionType::Asterisk, "Asterisk"},
    {ExpressionType::Slash, "Slash"},
    {ExpressionType::Percentage, "Percentage"},
    {ExpressionType::Caret, "Caret"},
    {ExpressionType::Equals, "Equals"},
    {ExpressionType::NotEquals, "NotEquals"},
    {ExpressionType::Less, "Less"},
    {ExpressionType::LessEquals, "LessEquals"},
    {ExpressionType::Greater, "Greater"},
    {ExpressionType::GreaterEquals, "GreaterEquals"},
    {ExpressionType::Like, "Like"},
    {ExpressionType::NotLike, "NotLike"},
    {ExpressionType::And, "And"},
    {ExpressionType::Or, "Or"},
    {ExpressionType::In, "In"},
    {ExpressionType::Not, "Not"},
    {ExpressionType::IsNull, "IsNull"},
    {ExpressionType::Exists, "Exists"},
    {ExpressionType::Between, "Between"},
    {ExpressionType::Hint, "Hint"},
    {ExpressionType::Case, "Case"},
};

// TODO(mp): this should be case-insensitive
const std::unordered_map<std::string, AggregateFunction> string_to_aggregate_function = {
    {"MIN", Min}, {"MAX", Max}, {"SUM", Sum}, {"AVG", Avg}, {"COUNT", Count},
};
}  // namespace opossum
