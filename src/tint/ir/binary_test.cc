// Copyright 2022 The Tint Authors.
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

#include "src/tint/ir/instruction.h"
#include "src/tint/ir/test_helper.h"
#include "src/tint/utils/string_stream.h"

namespace tint::ir {
namespace {

using namespace tint::number_suffixes;  // NOLINT
                                        //
using IR_InstructionTest = TestHelper;

TEST_F(IR_InstructionTest, CreateAnd) {
    auto& b = CreateEmptyBuilder();

    b.builder.next_runtime_id = Runtime::Id(42);
    const auto* inst = b.builder.And(b.builder.ir.types.Get<type::I32>(), b.builder.Constant(4_i),
                                     b.builder.Constant(2_i));

    EXPECT_EQ(inst->GetKind(), Binary::Kind::kAnd);

    ASSERT_TRUE(inst->Result()->Is<Runtime>());
    ASSERT_NE(inst->Result()->Type(), nullptr);
    EXPECT_EQ(Runtime::Id(42), inst->Result()->As<Runtime>()->AsId());

    ASSERT_TRUE(inst->LHS()->Is<Constant>());
    auto lhs = inst->LHS()->As<Constant>()->value;
    ASSERT_TRUE(lhs->Is<constant::Scalar<i32>>());
    EXPECT_EQ(4_i, lhs->As<constant::Scalar<i32>>()->ValueAs<i32>());

    ASSERT_TRUE(inst->RHS()->Is<Constant>());
    auto rhs = inst->RHS()->As<Constant>()->value;
    ASSERT_TRUE(rhs->Is<constant::Scalar<i32>>());
    EXPECT_EQ(2_i, rhs->As<constant::Scalar<i32>>()->ValueAs<i32>());

    utils::StringStream str;
    inst->ToString(str);
    EXPECT_EQ(str.str(), "%42 (i32) = 4 & 2");
}

TEST_F(IR_InstructionTest, CreateOr) {
    auto& b = CreateEmptyBuilder();

    b.builder.next_runtime_id = Runtime::Id(42);
    const auto* inst = b.builder.Or(b.builder.ir.types.Get<type::I32>(), b.builder.Constant(4_i),
                                    b.builder.Constant(2_i));

    EXPECT_EQ(inst->GetKind(), Binary::Kind::kOr);

    ASSERT_TRUE(inst->Result()->Is<Runtime>());
    EXPECT_EQ(Runtime::Id(42), inst->Result()->As<Runtime>()->AsId());

    ASSERT_TRUE(inst->LHS()->Is<Constant>());
    auto lhs = inst->LHS()->As<Constant>()->value;
    ASSERT_TRUE(lhs->Is<constant::Scalar<i32>>());
    EXPECT_EQ(4_i, lhs->As<constant::Scalar<i32>>()->ValueAs<i32>());

    ASSERT_TRUE(inst->RHS()->Is<Constant>());
    auto rhs = inst->RHS()->As<Constant>()->value;
    ASSERT_TRUE(rhs->Is<constant::Scalar<i32>>());
    EXPECT_EQ(2_i, rhs->As<constant::Scalar<i32>>()->ValueAs<i32>());

    utils::StringStream str;
    inst->ToString(str);
    EXPECT_EQ(str.str(), "%42 (i32) = 4 | 2");
}

TEST_F(IR_InstructionTest, CreateXor) {
    auto& b = CreateEmptyBuilder();

    b.builder.next_runtime_id = Runtime::Id(42);
    const auto* inst = b.builder.Xor(b.builder.ir.types.Get<type::I32>(), b.builder.Constant(4_i),
                                     b.builder.Constant(2_i));

    EXPECT_EQ(inst->GetKind(), Binary::Kind::kXor);

    ASSERT_TRUE(inst->Result()->Is<Runtime>());
    EXPECT_EQ(Runtime::Id(42), inst->Result()->As<Runtime>()->AsId());

    ASSERT_TRUE(inst->LHS()->Is<Constant>());
    auto lhs = inst->LHS()->As<Constant>()->value;
    ASSERT_TRUE(lhs->Is<constant::Scalar<i32>>());
    EXPECT_EQ(4_i, lhs->As<constant::Scalar<i32>>()->ValueAs<i32>());

    ASSERT_TRUE(inst->RHS()->Is<Constant>());
    auto rhs = inst->RHS()->As<Constant>()->value;
    ASSERT_TRUE(rhs->Is<constant::Scalar<i32>>());
    EXPECT_EQ(2_i, rhs->As<constant::Scalar<i32>>()->ValueAs<i32>());

    utils::StringStream str;
    inst->ToString(str);
    EXPECT_EQ(str.str(), "%42 (i32) = 4 ^ 2");
}

TEST_F(IR_InstructionTest, CreateLogicalAnd) {
    auto& b = CreateEmptyBuilder();

    b.builder.next_runtime_id = Runtime::Id(42);
    const auto* inst = b.builder.LogicalAnd(b.builder.ir.types.Get<type::Bool>(),
                                            b.builder.Constant(4_i), b.builder.Constant(2_i));

    EXPECT_EQ(inst->GetKind(), Binary::Kind::kLogicalAnd);

    ASSERT_TRUE(inst->Result()->Is<Runtime>());
    EXPECT_EQ(Runtime::Id(42), inst->Result()->As<Runtime>()->AsId());

    ASSERT_TRUE(inst->LHS()->Is<Constant>());
    auto lhs = inst->LHS()->As<Constant>()->value;
    ASSERT_TRUE(lhs->Is<constant::Scalar<i32>>());
    EXPECT_EQ(4_i, lhs->As<constant::Scalar<i32>>()->ValueAs<i32>());

    ASSERT_TRUE(inst->RHS()->Is<Constant>());
    auto rhs = inst->RHS()->As<Constant>()->value;
    ASSERT_TRUE(rhs->Is<constant::Scalar<i32>>());
    EXPECT_EQ(2_i, rhs->As<constant::Scalar<i32>>()->ValueAs<i32>());

    utils::StringStream str;
    inst->ToString(str);
    EXPECT_EQ(str.str(), "%42 (bool) = 4 && 2");
}

TEST_F(IR_InstructionTest, CreateLogicalOr) {
    auto& b = CreateEmptyBuilder();

    b.builder.next_runtime_id = Runtime::Id(42);
    const auto* inst = b.builder.LogicalOr(b.builder.ir.types.Get<type::Bool>(),
                                           b.builder.Constant(4_i), b.builder.Constant(2_i));

    EXPECT_EQ(inst->GetKind(), Binary::Kind::kLogicalOr);

    ASSERT_TRUE(inst->Result()->Is<Runtime>());
    EXPECT_EQ(Runtime::Id(42), inst->Result()->As<Runtime>()->AsId());

    ASSERT_TRUE(inst->LHS()->Is<Constant>());
    auto lhs = inst->LHS()->As<Constant>()->value;
    ASSERT_TRUE(lhs->Is<constant::Scalar<i32>>());
    EXPECT_EQ(4_i, lhs->As<constant::Scalar<i32>>()->ValueAs<i32>());

    ASSERT_TRUE(inst->RHS()->Is<Constant>());
    auto rhs = inst->RHS()->As<Constant>()->value;
    ASSERT_TRUE(rhs->Is<constant::Scalar<i32>>());
    EXPECT_EQ(2_i, rhs->As<constant::Scalar<i32>>()->ValueAs<i32>());

    utils::StringStream str;
    inst->ToString(str);
    EXPECT_EQ(str.str(), "%42 (bool) = 4 || 2");
}

TEST_F(IR_InstructionTest, CreateEqual) {
    auto& b = CreateEmptyBuilder();

    b.builder.next_runtime_id = Runtime::Id(42);
    const auto* inst = b.builder.Equal(b.builder.ir.types.Get<type::Bool>(),
                                       b.builder.Constant(4_i), b.builder.Constant(2_i));

    EXPECT_EQ(inst->GetKind(), Binary::Kind::kEqual);

    ASSERT_TRUE(inst->Result()->Is<Runtime>());
    EXPECT_EQ(Runtime::Id(42), inst->Result()->As<Runtime>()->AsId());

    ASSERT_TRUE(inst->LHS()->Is<Constant>());
    auto lhs = inst->LHS()->As<Constant>()->value;
    ASSERT_TRUE(lhs->Is<constant::Scalar<i32>>());
    EXPECT_EQ(4_i, lhs->As<constant::Scalar<i32>>()->ValueAs<i32>());

    ASSERT_TRUE(inst->RHS()->Is<Constant>());
    auto rhs = inst->RHS()->As<Constant>()->value;
    ASSERT_TRUE(rhs->Is<constant::Scalar<i32>>());
    EXPECT_EQ(2_i, rhs->As<constant::Scalar<i32>>()->ValueAs<i32>());

    utils::StringStream str;
    inst->ToString(str);
    EXPECT_EQ(str.str(), "%42 (bool) = 4 == 2");
}

TEST_F(IR_InstructionTest, CreateNotEqual) {
    auto& b = CreateEmptyBuilder();

    b.builder.next_runtime_id = Runtime::Id(42);
    const auto* inst = b.builder.NotEqual(b.builder.ir.types.Get<type::Bool>(),
                                          b.builder.Constant(4_i), b.builder.Constant(2_i));

    EXPECT_EQ(inst->GetKind(), Binary::Kind::kNotEqual);

    ASSERT_TRUE(inst->Result()->Is<Runtime>());
    EXPECT_EQ(Runtime::Id(42), inst->Result()->As<Runtime>()->AsId());

    ASSERT_TRUE(inst->LHS()->Is<Constant>());
    auto lhs = inst->LHS()->As<Constant>()->value;
    ASSERT_TRUE(lhs->Is<constant::Scalar<i32>>());
    EXPECT_EQ(4_i, lhs->As<constant::Scalar<i32>>()->ValueAs<i32>());

    ASSERT_TRUE(inst->RHS()->Is<Constant>());
    auto rhs = inst->RHS()->As<Constant>()->value;
    ASSERT_TRUE(rhs->Is<constant::Scalar<i32>>());
    EXPECT_EQ(2_i, rhs->As<constant::Scalar<i32>>()->ValueAs<i32>());

    utils::StringStream str;
    inst->ToString(str);
    EXPECT_EQ(str.str(), "%42 (bool) = 4 != 2");
}

TEST_F(IR_InstructionTest, CreateLessThan) {
    auto& b = CreateEmptyBuilder();

    b.builder.next_runtime_id = Runtime::Id(42);
    const auto* inst = b.builder.LessThan(b.builder.ir.types.Get<type::Bool>(),
                                          b.builder.Constant(4_i), b.builder.Constant(2_i));

    EXPECT_EQ(inst->GetKind(), Binary::Kind::kLessThan);

    ASSERT_TRUE(inst->Result()->Is<Runtime>());
    EXPECT_EQ(Runtime::Id(42), inst->Result()->As<Runtime>()->AsId());

    ASSERT_TRUE(inst->LHS()->Is<Constant>());
    auto lhs = inst->LHS()->As<Constant>()->value;
    ASSERT_TRUE(lhs->Is<constant::Scalar<i32>>());
    EXPECT_EQ(4_i, lhs->As<constant::Scalar<i32>>()->ValueAs<i32>());

    ASSERT_TRUE(inst->RHS()->Is<Constant>());
    auto rhs = inst->RHS()->As<Constant>()->value;
    ASSERT_TRUE(rhs->Is<constant::Scalar<i32>>());
    EXPECT_EQ(2_i, rhs->As<constant::Scalar<i32>>()->ValueAs<i32>());

    utils::StringStream str;
    inst->ToString(str);
    EXPECT_EQ(str.str(), "%42 (bool) = 4 < 2");
}

TEST_F(IR_InstructionTest, CreateGreaterThan) {
    auto& b = CreateEmptyBuilder();

    b.builder.next_runtime_id = Runtime::Id(42);
    const auto* inst = b.builder.GreaterThan(b.builder.ir.types.Get<type::Bool>(),
                                             b.builder.Constant(4_i), b.builder.Constant(2_i));

    EXPECT_EQ(inst->GetKind(), Binary::Kind::kGreaterThan);

    ASSERT_TRUE(inst->Result()->Is<Runtime>());
    EXPECT_EQ(Runtime::Id(42), inst->Result()->As<Runtime>()->AsId());

    ASSERT_TRUE(inst->LHS()->Is<Constant>());
    auto lhs = inst->LHS()->As<Constant>()->value;
    ASSERT_TRUE(lhs->Is<constant::Scalar<i32>>());
    EXPECT_EQ(4_i, lhs->As<constant::Scalar<i32>>()->ValueAs<i32>());

    ASSERT_TRUE(inst->RHS()->Is<Constant>());
    auto rhs = inst->RHS()->As<Constant>()->value;
    ASSERT_TRUE(rhs->Is<constant::Scalar<i32>>());
    EXPECT_EQ(2_i, rhs->As<constant::Scalar<i32>>()->ValueAs<i32>());

    utils::StringStream str;
    inst->ToString(str);
    EXPECT_EQ(str.str(), "%42 (bool) = 4 > 2");
}

TEST_F(IR_InstructionTest, CreateLessThanEqual) {
    auto& b = CreateEmptyBuilder();

    b.builder.next_runtime_id = Runtime::Id(42);
    const auto* inst = b.builder.LessThanEqual(b.builder.ir.types.Get<type::Bool>(),
                                               b.builder.Constant(4_i), b.builder.Constant(2_i));

    EXPECT_EQ(inst->GetKind(), Binary::Kind::kLessThanEqual);

    ASSERT_TRUE(inst->Result()->Is<Runtime>());
    EXPECT_EQ(Runtime::Id(42), inst->Result()->As<Runtime>()->AsId());

    ASSERT_TRUE(inst->LHS()->Is<Constant>());
    auto lhs = inst->LHS()->As<Constant>()->value;
    ASSERT_TRUE(lhs->Is<constant::Scalar<i32>>());
    EXPECT_EQ(4_i, lhs->As<constant::Scalar<i32>>()->ValueAs<i32>());

    ASSERT_TRUE(inst->RHS()->Is<Constant>());
    auto rhs = inst->RHS()->As<Constant>()->value;
    ASSERT_TRUE(rhs->Is<constant::Scalar<i32>>());
    EXPECT_EQ(2_i, rhs->As<constant::Scalar<i32>>()->ValueAs<i32>());

    utils::StringStream str;
    inst->ToString(str);
    EXPECT_EQ(str.str(), "%42 (bool) = 4 <= 2");
}

TEST_F(IR_InstructionTest, CreateGreaterThanEqual) {
    auto& b = CreateEmptyBuilder();

    b.builder.next_runtime_id = Runtime::Id(42);
    const auto* inst = b.builder.GreaterThanEqual(b.builder.ir.types.Get<type::Bool>(),
                                                  b.builder.Constant(4_i), b.builder.Constant(2_i));

    EXPECT_EQ(inst->GetKind(), Binary::Kind::kGreaterThanEqual);

    ASSERT_TRUE(inst->Result()->Is<Runtime>());
    EXPECT_EQ(Runtime::Id(42), inst->Result()->As<Runtime>()->AsId());

    ASSERT_TRUE(inst->LHS()->Is<Constant>());
    auto lhs = inst->LHS()->As<Constant>()->value;
    ASSERT_TRUE(lhs->Is<constant::Scalar<i32>>());
    EXPECT_EQ(4_i, lhs->As<constant::Scalar<i32>>()->ValueAs<i32>());

    ASSERT_TRUE(inst->RHS()->Is<Constant>());
    auto rhs = inst->RHS()->As<Constant>()->value;
    ASSERT_TRUE(rhs->Is<constant::Scalar<i32>>());
    EXPECT_EQ(2_i, rhs->As<constant::Scalar<i32>>()->ValueAs<i32>());

    utils::StringStream str;
    inst->ToString(str);
    EXPECT_EQ(str.str(), "%42 (bool) = 4 >= 2");
}

TEST_F(IR_InstructionTest, CreateShiftLeft) {
    auto& b = CreateEmptyBuilder();

    b.builder.next_runtime_id = Runtime::Id(42);
    const auto* inst = b.builder.ShiftLeft(b.builder.ir.types.Get<type::I32>(),
                                           b.builder.Constant(4_i), b.builder.Constant(2_i));

    EXPECT_EQ(inst->GetKind(), Binary::Kind::kShiftLeft);

    ASSERT_TRUE(inst->Result()->Is<Runtime>());
    EXPECT_EQ(Runtime::Id(42), inst->Result()->As<Runtime>()->AsId());

    ASSERT_TRUE(inst->LHS()->Is<Constant>());
    auto lhs = inst->LHS()->As<Constant>()->value;
    ASSERT_TRUE(lhs->Is<constant::Scalar<i32>>());
    EXPECT_EQ(4_i, lhs->As<constant::Scalar<i32>>()->ValueAs<i32>());

    ASSERT_TRUE(inst->RHS()->Is<Constant>());
    auto rhs = inst->RHS()->As<Constant>()->value;
    ASSERT_TRUE(rhs->Is<constant::Scalar<i32>>());
    EXPECT_EQ(2_i, rhs->As<constant::Scalar<i32>>()->ValueAs<i32>());

    utils::StringStream str;
    inst->ToString(str);
    EXPECT_EQ(str.str(), "%42 (i32) = 4 << 2");
}

TEST_F(IR_InstructionTest, CreateShiftRight) {
    auto& b = CreateEmptyBuilder();

    b.builder.next_runtime_id = Runtime::Id(42);
    const auto* inst = b.builder.ShiftRight(b.builder.ir.types.Get<type::I32>(),
                                            b.builder.Constant(4_i), b.builder.Constant(2_i));

    EXPECT_EQ(inst->GetKind(), Binary::Kind::kShiftRight);

    ASSERT_TRUE(inst->Result()->Is<Runtime>());
    EXPECT_EQ(Runtime::Id(42), inst->Result()->As<Runtime>()->AsId());

    ASSERT_TRUE(inst->LHS()->Is<Constant>());
    auto lhs = inst->LHS()->As<Constant>()->value;
    ASSERT_TRUE(lhs->Is<constant::Scalar<i32>>());
    EXPECT_EQ(4_i, lhs->As<constant::Scalar<i32>>()->ValueAs<i32>());

    ASSERT_TRUE(inst->RHS()->Is<Constant>());
    auto rhs = inst->RHS()->As<Constant>()->value;
    ASSERT_TRUE(rhs->Is<constant::Scalar<i32>>());
    EXPECT_EQ(2_i, rhs->As<constant::Scalar<i32>>()->ValueAs<i32>());

    utils::StringStream str;
    inst->ToString(str);
    EXPECT_EQ(str.str(), "%42 (i32) = 4 >> 2");
}

TEST_F(IR_InstructionTest, CreateAdd) {
    auto& b = CreateEmptyBuilder();

    b.builder.next_runtime_id = Runtime::Id(42);
    const auto* inst = b.builder.Add(b.builder.ir.types.Get<type::I32>(), b.builder.Constant(4_i),
                                     b.builder.Constant(2_i));

    EXPECT_EQ(inst->GetKind(), Binary::Kind::kAdd);

    ASSERT_TRUE(inst->Result()->Is<Runtime>());
    EXPECT_EQ(Runtime::Id(42), inst->Result()->As<Runtime>()->AsId());

    ASSERT_TRUE(inst->LHS()->Is<Constant>());
    auto lhs = inst->LHS()->As<Constant>()->value;
    ASSERT_TRUE(lhs->Is<constant::Scalar<i32>>());
    EXPECT_EQ(4_i, lhs->As<constant::Scalar<i32>>()->ValueAs<i32>());

    ASSERT_TRUE(inst->RHS()->Is<Constant>());
    auto rhs = inst->RHS()->As<Constant>()->value;
    ASSERT_TRUE(rhs->Is<constant::Scalar<i32>>());
    EXPECT_EQ(2_i, rhs->As<constant::Scalar<i32>>()->ValueAs<i32>());

    utils::StringStream str;
    inst->ToString(str);
    EXPECT_EQ(str.str(), "%42 (i32) = 4 + 2");
}

TEST_F(IR_InstructionTest, CreateSubtract) {
    auto& b = CreateEmptyBuilder();

    b.builder.next_runtime_id = Runtime::Id(42);
    const auto* inst = b.builder.Subtract(b.builder.ir.types.Get<type::I32>(),
                                          b.builder.Constant(4_i), b.builder.Constant(2_i));

    EXPECT_EQ(inst->GetKind(), Binary::Kind::kSubtract);

    ASSERT_TRUE(inst->Result()->Is<Runtime>());
    EXPECT_EQ(Runtime::Id(42), inst->Result()->As<Runtime>()->AsId());

    ASSERT_TRUE(inst->LHS()->Is<Constant>());
    auto lhs = inst->LHS()->As<Constant>()->value;
    ASSERT_TRUE(lhs->Is<constant::Scalar<i32>>());
    EXPECT_EQ(4_i, lhs->As<constant::Scalar<i32>>()->ValueAs<i32>());

    ASSERT_TRUE(inst->RHS()->Is<Constant>());
    auto rhs = inst->RHS()->As<Constant>()->value;
    ASSERT_TRUE(rhs->Is<constant::Scalar<i32>>());
    EXPECT_EQ(2_i, rhs->As<constant::Scalar<i32>>()->ValueAs<i32>());

    utils::StringStream str;
    inst->ToString(str);
    EXPECT_EQ(str.str(), "%42 (i32) = 4 - 2");
}

TEST_F(IR_InstructionTest, CreateMultiply) {
    auto& b = CreateEmptyBuilder();

    b.builder.next_runtime_id = Runtime::Id(42);
    const auto* inst = b.builder.Multiply(b.builder.ir.types.Get<type::I32>(),
                                          b.builder.Constant(4_i), b.builder.Constant(2_i));

    EXPECT_EQ(inst->GetKind(), Binary::Kind::kMultiply);

    ASSERT_TRUE(inst->Result()->Is<Runtime>());
    EXPECT_EQ(Runtime::Id(42), inst->Result()->As<Runtime>()->AsId());

    ASSERT_TRUE(inst->LHS()->Is<Constant>());
    auto lhs = inst->LHS()->As<Constant>()->value;
    ASSERT_TRUE(lhs->Is<constant::Scalar<i32>>());
    EXPECT_EQ(4_i, lhs->As<constant::Scalar<i32>>()->ValueAs<i32>());

    ASSERT_TRUE(inst->RHS()->Is<Constant>());
    auto rhs = inst->RHS()->As<Constant>()->value;
    ASSERT_TRUE(rhs->Is<constant::Scalar<i32>>());
    EXPECT_EQ(2_i, rhs->As<constant::Scalar<i32>>()->ValueAs<i32>());

    utils::StringStream str;
    inst->ToString(str);
    EXPECT_EQ(str.str(), "%42 (i32) = 4 * 2");
}

TEST_F(IR_InstructionTest, CreateDivide) {
    auto& b = CreateEmptyBuilder();

    b.builder.next_runtime_id = Runtime::Id(42);
    const auto* inst = b.builder.Divide(b.builder.ir.types.Get<type::I32>(),
                                        b.builder.Constant(4_i), b.builder.Constant(2_i));

    EXPECT_EQ(inst->GetKind(), Binary::Kind::kDivide);

    ASSERT_TRUE(inst->Result()->Is<Runtime>());
    EXPECT_EQ(Runtime::Id(42), inst->Result()->As<Runtime>()->AsId());

    ASSERT_TRUE(inst->LHS()->Is<Constant>());
    auto lhs = inst->LHS()->As<Constant>()->value;
    ASSERT_TRUE(lhs->Is<constant::Scalar<i32>>());
    EXPECT_EQ(4_i, lhs->As<constant::Scalar<i32>>()->ValueAs<i32>());

    ASSERT_TRUE(inst->RHS()->Is<Constant>());
    auto rhs = inst->RHS()->As<Constant>()->value;
    ASSERT_TRUE(rhs->Is<constant::Scalar<i32>>());
    EXPECT_EQ(2_i, rhs->As<constant::Scalar<i32>>()->ValueAs<i32>());

    utils::StringStream str;
    inst->ToString(str);
    EXPECT_EQ(str.str(), "%42 (i32) = 4 / 2");
}

TEST_F(IR_InstructionTest, CreateModulo) {
    auto& b = CreateEmptyBuilder();

    b.builder.next_runtime_id = Runtime::Id(42);
    const auto* inst = b.builder.Modulo(b.builder.ir.types.Get<type::I32>(),
                                        b.builder.Constant(4_i), b.builder.Constant(2_i));

    EXPECT_EQ(inst->GetKind(), Binary::Kind::kModulo);

    ASSERT_TRUE(inst->Result()->Is<Runtime>());
    EXPECT_EQ(Runtime::Id(42), inst->Result()->As<Runtime>()->AsId());

    ASSERT_TRUE(inst->LHS()->Is<Constant>());
    auto lhs = inst->LHS()->As<Constant>()->value;
    ASSERT_TRUE(lhs->Is<constant::Scalar<i32>>());
    EXPECT_EQ(4_i, lhs->As<constant::Scalar<i32>>()->ValueAs<i32>());

    ASSERT_TRUE(inst->RHS()->Is<Constant>());
    auto rhs = inst->RHS()->As<Constant>()->value;
    ASSERT_TRUE(rhs->Is<constant::Scalar<i32>>());
    EXPECT_EQ(2_i, rhs->As<constant::Scalar<i32>>()->ValueAs<i32>());

    utils::StringStream str;
    inst->ToString(str);
    EXPECT_EQ(str.str(), "%42 (i32) = 4 % 2");
}

TEST_F(IR_InstructionTest, Binary_Usage) {
    auto& b = CreateEmptyBuilder();

    b.builder.next_runtime_id = Runtime::Id(42);
    const auto* inst = b.builder.And(b.builder.ir.types.Get<type::I32>(), b.builder.Constant(4_i),
                                     b.builder.Constant(2_i));

    EXPECT_EQ(inst->GetKind(), Binary::Kind::kAnd);

    ASSERT_NE(inst->Result(), nullptr);
    ASSERT_EQ(inst->Result()->Usage().Length(), 1u);
    EXPECT_EQ(inst->Result()->Usage()[0], inst);

    ASSERT_NE(inst->LHS(), nullptr);
    ASSERT_EQ(inst->LHS()->Usage().Length(), 1u);
    EXPECT_EQ(inst->LHS()->Usage()[0], inst);

    ASSERT_NE(inst->RHS(), nullptr);
    ASSERT_EQ(inst->RHS()->Usage().Length(), 1u);
    EXPECT_EQ(inst->RHS()->Usage()[0], inst);
}

TEST_F(IR_InstructionTest, Binary_Usage_DuplicateValue) {
    auto& b = CreateEmptyBuilder();

    auto val = b.builder.Constant(4_i);

    b.builder.next_runtime_id = Runtime::Id(42);
    const auto* inst = b.builder.And(b.builder.ir.types.Get<type::I32>(), val, val);

    EXPECT_EQ(inst->GetKind(), Binary::Kind::kAnd);

    ASSERT_NE(inst->Result(), nullptr);
    ASSERT_EQ(inst->Result()->Usage().Length(), 1u);
    EXPECT_EQ(inst->Result()->Usage()[0], inst);

    ASSERT_EQ(inst->LHS(), inst->RHS());

    ASSERT_NE(inst->LHS(), nullptr);
    ASSERT_EQ(inst->LHS()->Usage().Length(), 1u);
    EXPECT_EQ(inst->LHS()->Usage()[0], inst);
}

}  // namespace
}  // namespace tint::ir
