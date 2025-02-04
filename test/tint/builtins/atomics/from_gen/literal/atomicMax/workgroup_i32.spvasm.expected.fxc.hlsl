static uint local_invocation_index_1 = 0u;
groupshared int arg_0;

void atomicMax_a89cc3() {
  int res = 0;
  int atomic_result = 0;
  InterlockedMax(arg_0, 1, atomic_result);
  int x_11 = atomic_result;
  res = x_11;
  return;
}

void compute_main_inner(uint local_invocation_index_2) {
  int atomic_result_1 = 0;
  InterlockedExchange(arg_0, 0, atomic_result_1);
  GroupMemoryBarrierWithGroupSync();
  atomicMax_a89cc3();
  return;
}

void compute_main_1() {
  uint x_31 = local_invocation_index_1;
  compute_main_inner(x_31);
  return;
}

struct tint_symbol_1 {
  uint local_invocation_index_1_param : SV_GroupIndex;
};

void compute_main_inner_1(uint local_invocation_index_1_param) {
  {
    int atomic_result_2 = 0;
    InterlockedExchange(arg_0, 0, atomic_result_2);
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
