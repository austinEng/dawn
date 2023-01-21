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

#ifndef SRC_TINT_READER_SPIRV_PARSER_TYPE_H_
#define SRC_TINT_READER_SPIRV_PARSER_TYPE_H_

#include <memory>
#include <string>
#include <vector>

#include "src/tint/ast/access.h"
#include "src/tint/ast/address_space.h"
#include "src/tint/ast/sampler.h"
#include "src/tint/ast/storage_texture.h"
#include "src/tint/castable.h"
#include "src/tint/type/texture_dimension.h"
#include "src/tint/utils/block_allocator.h"

// Forward declarations
namespace tint {
class ProgramBuilder;
}  // namespace tint
namespace tint::ast {
class Type;
}  // namespace tint::ast

namespace tint::reader::spirv {

/// Type is the base class for all types
class Type : public Castable<Type> {
  public:
    /// Constructor
    Type();
    /// Copy constructor
    Type(const Type&);
    /// Destructor
    ~Type() override;

    /// @param b the ProgramBuilder used to construct the AST types
    /// @returns the constructed ast::Type node for the given type
    virtual const ast::Type* Build(ProgramBuilder& b) const = 0;

    /// @returns the inner most store type if this is a pointer, `this` otherwise
    const Type* UnwrapPtr() const;

    /// @returns the inner most store type if this is a reference, `this`
    /// otherwise
    const Type* UnwrapRef() const;

    /// @returns the inner most aliased type if this is an alias, `this` otherwise
    const Type* UnwrapAlias() const;

    /// @returns the type with all aliasing, access control and pointers removed
    const Type* UnwrapAll() const;

    /// @returns true if this type is a float scalar
    bool IsFloatScalar() const;
    /// @returns true if this type is a float scalar or vector
    bool IsFloatScalarOrVector() const;
    /// @returns true if this type is a float vector
    bool IsFloatVector() const;
    /// @returns true if this type is an integer scalar
    bool IsIntegerScalar() const;
    /// @returns true if this type is an integer scalar or vector
    bool IsIntegerScalarOrVector() const;
    /// @returns true if this type is a scalar
    bool IsScalar() const;
    /// @returns true if this type is a signed integer vector
    bool IsSignedIntegerVector() const;
    /// @returns true if this type is a signed scalar or vector
    bool IsSignedScalarOrVector() const;
    /// @returns true if this type is an unsigned integer vector
    bool IsUnsignedIntegerVector() const;
    /// @returns true if this type is an unsigned scalar or vector
    bool IsUnsignedScalarOrVector() const;

#ifdef NDEBUG
    /// @returns "<no-type-info>", for debug purposes only
    std::string String() const { return "<no-type-info>"; }
#else
    /// @returns a string representation of the type, for debug purposes only
    virtual std::string String() const = 0;
#endif  // NDEBUG
};

/// TypeList is a list of Types
using TypeList = std::vector<const Type*>;

/// `void` type
struct Void final : public Castable<Void, Type> {
    /// @param b the ProgramBuilder used to construct the AST types
    /// @returns the constructed ast::Type node for the given type
    const ast::Type* Build(ProgramBuilder& b) const override;

#ifndef NDEBUG
    /// @returns a string representation of the type, for debug purposes only
    std::string String() const override;
#endif  // NDEBUG
};

/// `bool` type
struct Bool final : public Castable<Bool, Type> {
    /// @param b the ProgramBuilder used to construct the AST types
    /// @returns the constructed ast::Type node for the given type
    const ast::Type* Build(ProgramBuilder& b) const override;

#ifndef NDEBUG
    /// @returns a string representation of the type, for debug purposes only
    std::string String() const override;
#endif  // NDEBUG
};

/// `u32` type
struct U32 final : public Castable<U32, Type> {
    /// @param b the ProgramBuilder used to construct the AST types
    /// @returns the constructed ast::Type node for the given type
    const ast::Type* Build(ProgramBuilder& b) const override;

#ifndef NDEBUG
    /// @returns a string representation of the type, for debug purposes only
    std::string String() const override;
#endif  // NDEBUG
};

/// `f32` type
struct F32 final : public Castable<F32, Type> {
    /// @param b the ProgramBuilder used to construct the AST types
    /// @returns the constructed ast::Type node for the given type
    const ast::Type* Build(ProgramBuilder& b) const override;

#ifndef NDEBUG
    /// @returns a string representation of the type, for debug purposes only
    std::string String() const override;
#endif  // NDEBUG
};

/// `i32` type
struct I32 final : public Castable<I32, Type> {
    /// @param b the ProgramBuilder used to construct the AST types
    /// @returns the constructed ast::Type node for the given type
    const ast::Type* Build(ProgramBuilder& b) const override;

#ifndef NDEBUG
    /// @returns a string representation of the type, for debug purposes only
    std::string String() const override;
#endif  // NDEBUG
};

/// `ptr<SC, T, AM>` type
struct Pointer final : public Castable<Pointer, Type> {
    /// Constructor
    /// @param ty the store type
    /// @param sc the pointer address space
    /// @param access the declared access mode
    Pointer(const Type* ty, ast::AddressSpace sc, ast::Access access);

    /// Copy constructor
    /// @param other the other type to copy
    Pointer(const Pointer& other);

    /// @param b the ProgramBuilder used to construct the AST types
    /// @returns the constructed ast::Type node for the given type
    const ast::Type* Build(ProgramBuilder& b) const override;

#ifndef NDEBUG
    /// @returns a string representation of the type, for debug purposes only
    std::string String() const override;
#endif  // NDEBUG

    /// the store type
    Type const* const type;
    /// the pointer address space
    ast::AddressSpace const address_space;
    /// the pointer declared access mode
    ast::Access const access;
};

/// `ref<SC, T, AM>` type
/// Note this has no AST representation, but is used for type tracking in the
/// reader.
struct Reference final : public Castable<Reference, Type> {
    /// Constructor
    /// @param ty the referenced type
    /// @param sc the reference address space
    /// @param access the reference declared access mode
    Reference(const Type* ty, ast::AddressSpace sc, ast::Access access);

    /// Copy constructor
    /// @param other the other type to copy
    Reference(const Reference& other);

    /// @param b the ProgramBuilder used to construct the AST types
    /// @returns the constructed ast::Type node for the given type
    const ast::Type* Build(ProgramBuilder& b) const override;

#ifndef NDEBUG
    /// @returns a string representation of the type, for debug purposes only
    std::string String() const override;
#endif  // NDEBUG

    /// the store type
    Type const* const type;
    /// the pointer address space
    ast::AddressSpace const address_space;
    /// the pointer declared access mode
    ast::Access const access;
};

/// `vecN<T>` type
struct Vector final : public Castable<Vector, Type> {
    /// Constructor
    /// @param ty the element type
    /// @param sz the number of elements in the vector
    Vector(const Type* ty, uint32_t sz);

    /// Copy constructor
    /// @param other the other type to copy
    Vector(const Vector& other);

    /// @param b the ProgramBuilder used to construct the AST types
    /// @returns the constructed ast::Type node for the given type
    const ast::Type* Build(ProgramBuilder& b) const override;

#ifndef NDEBUG
    /// @returns a string representation of the type, for debug purposes only
    std::string String() const override;
#endif  // NDEBUG

    /// the element type
    Type const* const type;
    /// the number of elements in the vector
    const uint32_t size;
};

/// `matNxM<T>` type
struct Matrix final : public Castable<Matrix, Type> {
    /// Constructor
    /// @param ty the matrix element type
    /// @param c the number of columns in the matrix
    /// @param r the number of rows in the matrix
    Matrix(const Type* ty, uint32_t c, uint32_t r);

    /// Copy constructor
    /// @param other the other type to copy
    Matrix(const Matrix& other);

    /// @param b the ProgramBuilder used to construct the AST types
    /// @returns the constructed ast::Type node for the given type
    const ast::Type* Build(ProgramBuilder& b) const override;

#ifndef NDEBUG
    /// @returns a string representation of the type, for debug purposes only
    std::string String() const override;
#endif  // NDEBUG

    /// the matrix element type
    Type const* const type;
    /// the number of columns in the matrix
    const uint32_t columns;
    /// the number of rows in the matrix
    const uint32_t rows;
};

/// `array<T, N>` type
struct Array final : public Castable<Array, Type> {
    /// Constructor
    /// @param el the element type
    /// @param sz the number of elements in the array. 0 represents runtime-sized
    /// array.
    /// @param st the byte stride of the array. 0 means use implicit stride.
    Array(const Type* el, uint32_t sz, uint32_t st);

    /// Copy constructor
    /// @param other the other type to copy
    Array(const Array& other);

    /// @param b the ProgramBuilder used to construct the AST types
    /// @returns the constructed ast::Type node for the given type
    const ast::Type* Build(ProgramBuilder& b) const override;

#ifndef NDEBUG
    /// @returns a string representation of the type, for debug purposes only
    std::string String() const override;
#endif  // NDEBUG

    /// the element type
    Type const* const type;
    /// the number of elements in the array. 0 represents runtime-sized array.
    const uint32_t size;
    /// the byte stride of the array
    const uint32_t stride;
};

/// `sampler` type
struct Sampler final : public Castable<Sampler, Type> {
    /// Constructor
    /// @param k the sampler kind
    explicit Sampler(ast::SamplerKind k);

    /// Copy constructor
    /// @param other the other type to copy
    Sampler(const Sampler& other);

    /// @param b the ProgramBuilder used to construct the AST types
    /// @returns the constructed ast::Type node for the given type
    const ast::Type* Build(ProgramBuilder& b) const override;

#ifndef NDEBUG
    /// @returns a string representation of the type, for debug purposes only
    std::string String() const override;
#endif  // NDEBUG

    /// the sampler kind
    ast::SamplerKind const kind;
};

/// Base class for texture types
struct Texture : public Castable<Texture, Type> {
    ~Texture() override;

    /// Constructor
    /// @param d the texture dimensions
    explicit Texture(type::TextureDimension d);

    /// Copy constructor
    /// @param other the other type to copy
    Texture(const Texture& other);

    /// the texture dimensions
    type::TextureDimension const dims;
};

/// `texture_depth_D` type
struct DepthTexture final : public Castable<DepthTexture, Texture> {
    /// Constructor
    /// @param d the texture dimensions
    explicit DepthTexture(type::TextureDimension d);

    /// Copy constructor
    /// @param other the other type to copy
    DepthTexture(const DepthTexture& other);

    /// @param b the ProgramBuilder used to construct the AST types
    /// @returns the constructed ast::Type node for the given type
    const ast::Type* Build(ProgramBuilder& b) const override;

#ifndef NDEBUG
    /// @returns a string representation of the type, for debug purposes only
    std::string String() const override;
#endif  // NDEBUG
};

/// `texture_depth_multisampled_D` type
struct DepthMultisampledTexture final : public Castable<DepthMultisampledTexture, Texture> {
    /// Constructor
    /// @param d the texture dimensions
    explicit DepthMultisampledTexture(type::TextureDimension d);

    /// Copy constructor
    /// @param other the other type to copy
    DepthMultisampledTexture(const DepthMultisampledTexture& other);

    /// @param b the ProgramBuilder used to construct the AST types
    /// @returns the constructed ast::Type node for the given type
    const ast::Type* Build(ProgramBuilder& b) const override;

#ifndef NDEBUG
    /// @returns a string representation of the type, for debug purposes only
    std::string String() const override;
#endif  // NDEBUG
};

/// `texture_multisampled_D<T>` type
struct MultisampledTexture final : public Castable<MultisampledTexture, Texture> {
    /// Constructor
    /// @param d the texture dimensions
    /// @param t the multisampled texture type
    MultisampledTexture(type::TextureDimension d, const Type* t);

    /// Copy constructor
    /// @param other the other type to copy
    MultisampledTexture(const MultisampledTexture& other);

    /// @param b the ProgramBuilder used to construct the AST types
    /// @returns the constructed ast::Type node for the given type
    const ast::Type* Build(ProgramBuilder& b) const override;

#ifndef NDEBUG
    /// @returns a string representation of the type, for debug purposes only
    std::string String() const override;
#endif  // NDEBUG

    /// the multisampled texture type
    Type const* const type;
};

/// `texture_D<T>` type
struct SampledTexture final : public Castable<SampledTexture, Texture> {
    /// Constructor
    /// @param d the texture dimensions
    /// @param t the sampled texture type
    SampledTexture(type::TextureDimension d, const Type* t);

    /// Copy constructor
    /// @param other the other type to copy
    SampledTexture(const SampledTexture& other);

    /// @param b the ProgramBuilder used to construct the AST types
    /// @returns the constructed ast::Type node for the given type
    const ast::Type* Build(ProgramBuilder& b) const override;

#ifndef NDEBUG
    /// @returns a string representation of the type, for debug purposes only
    std::string String() const override;
#endif  // NDEBUG

    /// the sampled texture type
    Type const* const type;
};

/// `texture_storage_D<F>` type
struct StorageTexture final : public Castable<StorageTexture, Texture> {
    /// Constructor
    /// @param d the texture dimensions
    /// @param f the storage image format
    /// @param a the access control
    StorageTexture(type::TextureDimension d, ast::TexelFormat f, ast::Access a);

    /// Copy constructor
    /// @param other the other type to copy
    StorageTexture(const StorageTexture& other);

    /// @param b the ProgramBuilder used to construct the AST types
    /// @returns the constructed ast::Type node for the given type
    const ast::Type* Build(ProgramBuilder& b) const override;

#ifndef NDEBUG
    /// @returns a string representation of the type, for debug purposes only
    std::string String() const override;
#endif  // NDEBUG

    /// the storage image format
    ast::TexelFormat const format;

    /// the access control
    ast::Access const access;
};

/// Base class for named types
struct Named : public Castable<Named, Type> {
    /// Constructor
    /// @param n the type name
    explicit Named(Symbol n);

    /// Copy constructor
    /// @param other the other type to copy
    Named(const Named& other);

    /// Destructor
    ~Named() override;

#ifndef NDEBUG
    /// @returns a string representation of the type, for debug purposes only
    std::string String() const override;
#endif  // NDEBUG

    /// the type name
    const Symbol name;
};

/// `type T = N` type
struct Alias final : public Castable<Alias, Named> {
    /// Constructor
    /// @param n the alias name
    /// @param t the aliased type
    Alias(Symbol n, const Type* t);

    /// Copy constructor
    /// @param other the other type to copy
    Alias(const Alias& other);

    /// @param b the ProgramBuilder used to construct the AST types
    /// @returns the constructed ast::Type node for the given type
    const ast::Type* Build(ProgramBuilder& b) const override;

    /// the aliased type
    Type const* const type;
};

/// `struct N { ... };` type
struct Struct final : public Castable<Struct, Named> {
    /// Constructor
    /// @param n the struct name
    /// @param m the member types
    Struct(Symbol n, TypeList m);

    /// Copy constructor
    /// @param other the other type to copy
    Struct(const Struct& other);

    /// Destructor
    ~Struct() override;

    /// @param b the ProgramBuilder used to construct the AST types
    /// @returns the constructed ast::Type node for the given type
    const ast::Type* Build(ProgramBuilder& b) const override;

    /// the member types
    const TypeList members;
};

/// A manager of types
class TypeManager {
  public:
    /// Constructor
    TypeManager();

    /// Destructor
    ~TypeManager();

    /// @return a Void type. Repeated calls will return the same pointer.
    const spirv::Void* Void();
    /// @return a Bool type. Repeated calls will return the same pointer.
    const spirv::Bool* Bool();
    /// @return a U32 type. Repeated calls will return the same pointer.
    const spirv::U32* U32();
    /// @return a F32 type. Repeated calls will return the same pointer.
    const spirv::F32* F32();
    /// @return a I32 type. Repeated calls will return the same pointer.
    const spirv::I32* I32();
    /// @param ty the input type.
    /// @returns the equivalent unsigned integer scalar or vector if @p ty is a scalar or vector,
    /// otherwise nullptr.
    const Type* AsUnsigned(const Type* ty);

    /// @param ty the store type
    /// @param address_space the pointer address space
    /// @param access the declared access mode
    /// @return a Pointer type. Repeated calls with the same arguments will return
    /// the same pointer.
    const spirv::Pointer* Pointer(const Type* ty,
                                  ast::AddressSpace address_space,
                                  ast::Access access = ast::Access::kUndefined);
    /// @param ty the referenced type
    /// @param address_space the reference address space
    /// @param access the declared access mode
    /// @return a Reference type. Repeated calls with the same arguments will
    /// return the same pointer.
    const spirv::Reference* Reference(const Type* ty,
                                      ast::AddressSpace address_space,
                                      ast::Access access = ast::Access::kUndefined);
    /// @param ty the element type
    /// @param sz the number of elements in the vector
    /// @return a Vector type. Repeated calls with the same arguments will return
    /// the same pointer.
    const spirv::Vector* Vector(const Type* ty, uint32_t sz);
    /// @param ty the matrix element type
    /// @param c the number of columns in the matrix
    /// @param r the number of rows in the matrix
    /// @return a Matrix type. Repeated calls with the same arguments will return
    /// the same pointer.
    const spirv::Matrix* Matrix(const Type* ty, uint32_t c, uint32_t r);
    /// @param el the element type
    /// @param sz the number of elements in the array. 0 represents runtime-sized
    /// array.
    /// @param st the byte stride of the array
    /// @return a Array type. Repeated calls with the same arguments will return
    /// the same pointer.
    const spirv::Array* Array(const Type* el, uint32_t sz, uint32_t st);
    /// @param n the alias name
    /// @param t the aliased type
    /// @return a Alias type. Repeated calls with the same arguments will return
    /// the same pointer.
    const spirv::Alias* Alias(Symbol n, const Type* t);
    /// @param n the struct name
    /// @param m the member types
    /// @return a Struct type. Repeated calls with the same arguments will return
    /// the same pointer.
    const spirv::Struct* Struct(Symbol n, TypeList m);
    /// @param k the sampler kind
    /// @return a Sampler type. Repeated calls with the same arguments will return
    /// the same pointer.
    const spirv::Sampler* Sampler(ast::SamplerKind k);
    /// @param d the texture dimensions
    /// @return a DepthTexture type. Repeated calls with the same arguments will
    /// return the same pointer.
    const spirv::DepthTexture* DepthTexture(type::TextureDimension d);
    /// @param d the texture dimensions
    /// @return a DepthMultisampledTexture type. Repeated calls with the same
    /// arguments will return the same pointer.
    const spirv::DepthMultisampledTexture* DepthMultisampledTexture(type::TextureDimension d);
    /// @param d the texture dimensions
    /// @param t the multisampled texture type
    /// @return a MultisampledTexture type. Repeated calls with the same arguments
    /// will return the same pointer.
    const spirv::MultisampledTexture* MultisampledTexture(type::TextureDimension d, const Type* t);
    /// @param d the texture dimensions
    /// @param t the sampled texture type
    /// @return a SampledTexture type. Repeated calls with the same arguments will
    /// return the same pointer.
    const spirv::SampledTexture* SampledTexture(type::TextureDimension d, const Type* t);
    /// @param d the texture dimensions
    /// @param f the storage image format
    /// @param a the access control
    /// @return a StorageTexture type. Repeated calls with the same arguments will
    /// return the same pointer.
    const spirv::StorageTexture* StorageTexture(type::TextureDimension d,
                                                ast::TexelFormat f,
                                                ast::Access a);

  private:
    struct State;
    std::unique_ptr<State> state;
};

}  // namespace tint::reader::spirv

#endif  // SRC_TINT_READER_SPIRV_PARSER_TYPE_H_
