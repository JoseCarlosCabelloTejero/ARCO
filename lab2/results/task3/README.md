# Tarea 3 - Resultados
En esta tarea el análisis que se ha llevado a cabo ha sido desde un nodo de cómputo de `devcloud`. 

Las caracteristicas del nodo son las siguientes:

    Architecture:                    x86_64
    CPU op-mode(s):                  32-bit, 64-bit
    Byte Order:                      Little Endian
    Address sizes:                   46 bits physical, 48 bits virtual
    CPU(s):                          24
    On-line CPU(s) list:             0-23
    Thread(s) per core:              2
    Core(s) per socket:              6
    Socket(s):                       2
    NUMA node(s):                    2
    Vendor ID:                       GenuineIntel
    CPU family:                      6
    Model:                           85
    Model name:                      Intel(R) Xeon(R) Gold 6128 CPU @ 3.40GHz
    Stepping:                        4
    CPU MHz:                         1252.642
    CPU max MHz:                     3700.0000
    CPU min MHz:                     1200.0000
    BogoMIPS:                        6800.00
    Virtualization:                  VT-x
    L1d cache:                       384 KiB
    L1i cache:                       384 KiB
    L2 cache:                        12 MiB
    L3 cache:                        38.5 MiB
    NUMA node0 CPU(s):               0-5,12-17
    NUMA node1 CPU(s):               6-11,18-23
    Vulnerability Itlb multihit:     KVM: Vulnerable
    Vulnerability L1tf:              Mitigation; PTE Inversion
    Vulnerability Mds:               Mitigation; Clear CPU buffers; SMT vulnerable
    Vulnerability Meltdown:          Mitigation; PTI
    Vulnerability Spec store bypass: Mitigation; Speculative Store Bypass disabled via prctl and seccomp
    Vulnerability Spectre v1:        Mitigation; usercopy/swapgs barriers and __user pointer sanitization
    Vulnerability Spectre v2:        Mitigation; Full generic retpoline, IBPB conditional, IBRS_FW, STIBP conditional, RSB filling
    Vulnerability Srbds:             Not affected
    Vulnerability Tsx async abort:   Mitigation; Clear CPU buffers; SMT vulnerable
    Flags:                           fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush dts acpi mmx fxsr sse sse2 ss ht tm pbe syscall nx pdpe1gb rdtscp lm constant_tsc art arch_perfmon pebs bts rep_good nopl xtopology nonstop_tsc cpuid aperfmperf pni pclmulqdq dtes64 monitor ds_cpl vmx smx est tm2 ssse3 sdbg fma cx16 xtpr pdcm pcid dca sse4_1 sse4_2 x2apic movbe popcnt tsc_deadline_timer aes xsave avx f16c rdrand lahf_lm abm 3dnowprefetch cpuid_fault epb cat_l3 cdp_l3 invpcid_single pti intel_ppin ssbd mba ibrs ibpb stibp tpr_shadow vnmi flexpriority ept vpid ept_ad fsgsbase tsc_adjust bmi1 hle avx2 smep bmi2 erms invpcid rtm cqm mpx rdt_a avx512f avx512dq rdseed adx smap clflushopt clwb intel_pt avx512cd avx512bw avx512vl xsaveopt xsavec xgetbv1 xsaves cqm_llc cqm_occup_llc cqm_mbm_total cqm_mbm_local dtherm ida arat pln pts hwp hwp_act_window hwp_epp hwp_pkg_req pku ospke md_clear flush_l1d

Para compilar se ha utilizado el comando:

    g++ -fopenmp -g src/matmul.cpp

Y para realizar el análisis con la herramienta de `advisor` desde `devcloud` se ha utilizado el siguiente comando:

    advisor --collect=roofline --project-dir=./advi_results --search-dir all:=./src -- ./a.out 

Según el [manual de intel de advisor para la opción collect](https://www.intel.com/content/www/us/en/develop/documentation/advisor-user-guide/top/command-line-interface/advisor-command-line-interface-reference/advisor-command-action-reference/collect.html), al indicar el argumento `roofline`, se ejecutará un analisis `Survey` e inmediatamente después un análisis de `Trip Counts` y `FLOP`. Con esto podremos ver una gráfico `roofline` desde el `advisor-gui`.

Para crear un `snapshot` se ha utilizado el siguiente comando:

    advisor --snapshot --pack --cache-sources --cache-binaries --project-dir=./advi_results

Ahora nos llevamos el archivo `snapshot000.advixeexpz` a nuestro PC y ahí podemos abrir los resultados desde la herramienta gráfica de `advisor-gui`. En esta imagen podemos ver el gráfico `roofline` mencionado anteriormente:

![Gráfico roofline](https://i.imgur.com/Zbug1Zv.png)
