# DP-CS Mock Communication

## Steps to Run
```
cmake -S . -B build_
cd build_/
make
cd mat_mul_dp/
./mat_mul_dp --compute-server0-port 1234 --compute-server1-port 1235 --dp-id 0 --fractional-bits 0
```