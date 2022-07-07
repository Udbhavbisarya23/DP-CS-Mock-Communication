# DP-CS Mock Communication

## Steps to Run
```
cmake -S . -B build_
cd build_/
make
cd neural_net_dp/
./image_provider --compute-server0-port 1234 --compute-server1-port 1235 --dp-id 0 --fractional-bits 0
```