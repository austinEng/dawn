struct S {
  int x;
  uint a;
  uint y;
};

groupshared S wg[10];

struct tint_symbol_1 {
  uint local_invocation_index : SV_GroupIndex;
};

void compute_main_inner(uint local_invocation_index) {
  {
    for(uint idx = local_invocation_index; (idx < 10u); idx = (idx + 1u)) {
      uint i = idx;
      wg[i].x = 0;
      uint atomic_result = 0u;
      InterlockedExchange(wg[i].a, 0u, atomic_result);
      wg[i].y = 0u;
    }
  }
  GroupMemoryBarrierWithGroupSync();
  uint atomic_result_1 = 0u;
  InterlockedExchange(wg[4].a, 1u, atomic_result_1);
}

[numthreads(1, 1, 1)]
void compute_main(tint_symbol_1 tint_symbol) {
  compute_main_inner(tint_symbol.local_invocation_index);
  return;
}
