static uint local_invocation_index_1 = 0u;
groupshared uint arg_0;

void atomicOr_5e3d61() {
  uint arg_1 = 0u;
  uint res = 0u;
  arg_1 = 1u;
  uint x_18 = arg_1;
  uint atomic_result = 0u;
  InterlockedOr(arg_0, x_18, atomic_result);
  uint x_14 = atomic_result;
  res = x_14;
  return;
}

void compute_main_inner(uint local_invocation_index_2) {
  uint atomic_result_1 = 0u;
  InterlockedExchange(arg_0, 0u, atomic_result_1);
  GroupMemoryBarrierWithGroupSync();
  atomicOr_5e3d61();
  return;
}

void compute_main_1() {
  uint x_32 = local_invocation_index_1;
  compute_main_inner(x_32);
  return;
}

struct tint_symbol_1 {
  uint local_invocation_index_1_param : SV_GroupIndex;
};

void compute_main_inner_1(uint local_invocation_index_1_param) {
  {
    uint atomic_result_2 = 0u;
    InterlockedExchange(arg_0, 0u, atomic_result_2);
  }
  GroupMemoryBarrierWithGroupSync();
  local_invocation_index_1 = local_invocation_index_1_param;
  compute_main_1();
}

[numthreads(1, 1, 1)]
void compute_main(tint_symbol_1 tint_symbol) {
  compute_main_inner_1(tint_symbol.local_invocation_index_1_param);
  return;
}
