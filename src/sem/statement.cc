// Copyright 2021 The Tint Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <algorithm>

#include "src/ast/block_statement.h"
#include "src/ast/loop_statement.h"
#include "src/ast/statement.h"
#include "src/sem/block_statement.h"
#include "src/sem/statement.h"

TINT_INSTANTIATE_TYPEINFO(tint::sem::Statement);

namespace tint {
namespace sem {

Statement::Statement(const ast::Statement* declaration, const Statement* parent)
    : declaration_(declaration), parent_(parent) {}

const BlockStatement* Statement::Block() const {
  auto* stmt = parent_;
  while (stmt != nullptr) {
    if (auto* block_stmt = stmt->As<BlockStatement>()) {
      return block_stmt;
    }
    stmt = stmt->parent_;
  }
  return nullptr;
}

const ast::Function* Statement::Function() const {
  if (auto* block = Block()) {
    if (auto* fbs = block->FindFirstParent<FunctionBlockStatement>()) {
      return fbs->Function();
    }
  }
  return nullptr;
}

}  // namespace sem
}  // namespace tint
