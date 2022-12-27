// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include <memory>

#include "flutter/fml/macros.h"
#include "impeller/geometry/matrix.h"
#include "impeller/geometry/vector.h"
#include "impeller/renderer/allocator.h"
#include "impeller/renderer/command.h"
#include "impeller/renderer/device_buffer.h"
#include "impeller/renderer/host_buffer.h"
#include "impeller/renderer/vertex_buffer.h"
#include "impeller/scene/importer/scene_flatbuffers.h"
#include "impeller/scene/pipeline_key.h"
#include "impeller/scene/scene_context.h"

namespace impeller {
namespace scene {

class CuboidGeometry;
class VertexBufferGeometry;

class Geometry {
 public:
  virtual ~Geometry();

  static std::shared_ptr<CuboidGeometry> MakeCuboid(Vector3 size);

  static std::shared_ptr<VertexBufferGeometry> MakeVertexBuffer(
      VertexBuffer vertex_buffer);

  static std::shared_ptr<VertexBufferGeometry> MakeFromFlatbuffer(
      const fb::MeshPrimitive& mesh,
      Allocator& allocator);

  virtual GeometryType GetGeometryType() const = 0;

  virtual VertexBuffer GetVertexBuffer(Allocator& allocator) const = 0;

  virtual void BindToCommand(const SceneContext& scene_context,
                             HostBuffer& buffer,
                             const Matrix& transform,
                             Command& command) const = 0;
};

class CuboidGeometry final : public Geometry {
 public:
  CuboidGeometry();

  ~CuboidGeometry() override;

  void SetSize(Vector3 size);

  // |Geometry|
  GeometryType GetGeometryType() const override;

  // |Geometry|
  VertexBuffer GetVertexBuffer(Allocator& allocator) const override;

  // |Geometry|
  void BindToCommand(const SceneContext& scene_context,
                     HostBuffer& buffer,
                     const Matrix& transform,
                     Command& command) const override;

 private:
  Vector3 size_;

  FML_DISALLOW_COPY_AND_ASSIGN(CuboidGeometry);
};

class VertexBufferGeometry final : public Geometry {
 public:
  VertexBufferGeometry();

  ~VertexBufferGeometry() override;

  void SetVertexBuffer(VertexBuffer vertex_buffer);

  // |Geometry|
  GeometryType GetGeometryType() const override;

  // |Geometry|
  VertexBuffer GetVertexBuffer(Allocator& allocator) const override;

  // |Geometry|
  void BindToCommand(const SceneContext& scene_context,
                     HostBuffer& buffer,
                     const Matrix& transform,
                     Command& command) const override;

 private:
  VertexBuffer vertex_buffer_;

  FML_DISALLOW_COPY_AND_ASSIGN(VertexBufferGeometry);
};

}  // namespace scene
}  // namespace impeller
