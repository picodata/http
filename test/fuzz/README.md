## Fuzzing

Clone to home dir
```bash
git clone https://github.com/llvm-mirror/compiler-rt.git
```

Build fuzzers
```bash
clang -fsanitize=fuzzer,fuzzer-no-link -g -I../../http tplevah_fuzzer.c -o tplevah_fuzzer
clang -fsanitize=fuzzer,fuzzer-no-link -g -I../../http httpfast_fuzzer.c -o httpfast_fuzzer
```

Run fuzzers
```bash
python3 test/fuzz/fuzz_until.py tpleval --libfuzzer-log tpleval.log --corpus-dir ./corpus/tpleval &
python3 test/fuzz/fuzz_until.py httpfast --libfuzzer-log httpfast.log --corpus-dir ./corpus/httpfast &
```

Build for reports
```bash
clang -fprofile-instr-generate -fcoverage-mapping -o httpfast_fuzzer -g -I../../http httpfast_fuzzer.c ~/compiler-rt/lib/fuzzer/standalone/StandaloneFuzzTargetMain.c
clang -fprofile-instr-generate -fcoverage-mapping -o tplevah_fuzzer -g -I../../http tplevah_fuzzer.c ~/compiler-rt/lib/fuzzer/standalone/StandaloneFuzzTargetMain.c
```

Generate reports
```bash
llvm-profdata merge -sparse httpfast.profraw -o httpfast.profdata
llvm-profdata merge -sparse tpleval.profraw -o tpleval.profdata

llvm-cov show ./test/fuzz/tpleval_fuzzer -instr-profile=tpleval.profdata -format=html -output-dir=coverage_tpleval
llvm-cov show ./test/fuzz/httpfast_fuzzer -instr-profile=httpfast.profdata -format=html -output-dir=coverage_tpleval
```