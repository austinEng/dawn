SKIP: FAILED

RWByteAddressBuffer prevent_dce : register(u0, space2);

void subgroupBroadcast_07e2d8() {
  float16_t arg_0 = float16_t(1.0h);
  float16_t res = WaveReadLaneAt(arg_0, 1u);
  prevent_dce.Store<float16_t>(0u, res);
}

[numthreads(1, 1, 1)]
void compute_main() {
  subgroupBroadcast_07e2d8();
  return;
}
