intrinsics/gen/modf/1d59e5.wgsl:29:24 warning: use of deprecated intrinsic
  var res: vec4<f32> = modf(vec4<f32>(), &arg_1);
                       ^^^^

groupshared float4 arg_1;

void modf_1d59e5() {
  float4 res = modf(float4(0.0f, 0.0f, 0.0f, 0.0f), arg_1);
}

struct tint_symbol_1 {
  uint local_invocation_index : SV_GroupIndex;
};

[numthreads(1, 1, 1)]
void compute_main(tint_symbol_1 tint_symbol) {
  const uint local_invocation_index = tint_symbol.local_invocation_index;
  if ((local_invocation_index == 0u)) {
    arg_1 = float4(0.0f, 0.0f, 0.0f, 0.0f);
  }
  GroupMemoryBarrierWithGroupSync();
  modf_1d59e5();
  return;
}
