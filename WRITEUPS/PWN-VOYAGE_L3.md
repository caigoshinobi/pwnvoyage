# PWNVOYAGE / GAME / PWN-VOYAGE_L3

As usual, let's start gathering some information about the level. We notice using the `strings` command that there are numerous MD5 hashes.

```

caigoshinobi@freyja:~$ file PWN-VOYAGE_L3
PWN-VOYAGE_L3: ELF 64-bit LSB pie executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, BuildID[sha1]=2648858438909b37726ebf8a86bbf89f2e254dfc, for GNU/Linux 3.2.0, not stripped

```

```

caigoshinobi@freyja:~$ strings PWN-VOYAGE_L3 | grep 'FLAG.txt REQUIRED' -B 30
GLIBC_2.2.5
PTE1
u+UH
AWAVAUATSH
[A\A]A^A_]
202cb962ac59075b964b07152d234b70
ec8956637a99787bd197eacd77acce5e
b73ce398c39f506af761d2277d853a92
5737034557ef5b8c02c0e46513b98f90
a2557a7b2e94197ff767970b67041697
d1f491a404d6854880943e5c3cd9ca25
c75b6f114c23a4d7ea11331e7c00e73c
e836d813fd184325132fca8edcdfb40e
38b3eff8baf56627478ec76a704e9b52
1385974ed5904a438616ff7bdb3f7439
df6d2338b2b8fce1ec2f6dda0a630eb0
959a557f5f6beb411fd954f3f34b21c3
bcbe3365e6ac95ea2c0343a2395834dd
65b9eea6e1cc6bb9f0cd2a47751a186f
d93ed5b6db83be78efb0d05ae420158e
250cf8b51c773f3f8dc8b4be867a9a02
b7892fb3c2f009c65f686f6355c895b5
a8849b052492b5106526b2331e526138
bca82e41ee7b0833588399b1fcd177c7
fe7ee8fc1959cc7214fa21c4840dff0a
02522a2b2726fb0a03bb19f2d8d9524d
d5cfead94f5350c12c322b5b664544c1
b2eeb7362ef83deff5c7813a67e14f0a
698d51a19d8a121ce581499d7b701668
------------------------------------------------------
| *FLAG.txt REQUIRED*                                |

```

Once again the level asks for the **FLAG.txt** file, so we proceed to compile it. 


Let's see what happens when we execute it:


```

caigoshinobi@freyja:~$ ./PWN-VOYAGE_L3

==============================================================

 ██▓    ▓█████ ██▒   █▓▓█████  ██▓           ██▓ ██▓ ██▓
▓██▒    ▓█   ▀▓██░   █▒▓█   ▀ ▓██▒          ▓██▓▓██▓▓██▒
▒██░    ▒███   ▓██  █▒░▒███   ▒██░          ▒██▒▒██▒▒██▒
▒██░    ▒▓█  ▄  ▒██ █░░▒▓█  ▄ ▒██░          ░██░░██░░██░
░██████▒░▒████▒  ▒▀█░  ░▒████▒░██████▒      ░██░░██░░██░
░ ▒░▓  ░░░ ▒░ ░  ░ ▐░  ░░ ▒░ ░░ ▒░▓  ░      ░▓  ░▓  ░▓
░ ░ ▒  ░ ░ ░  ░  ░ ░░   ░ ░  ░░ ░ ▒  ░       ▒ ░ ▒ ░ ▒
  ░ ░      ░       ░░     ░     ░ ░          ▒   ▒ ░ ▒ ░
====░==░===░==░=====░=====░==░====░==░=======░===░===░========
                    ░
Finally within the Vault, you cast your gaze around. The Sword
of Heroes must lie within one of these tombs. Yet, you are well
aware that guarding the sword is Grimshade, a legendary Wraith
and its last owner. The Vault, however, houses dozens of tombs
(and undeads). Shall you open them all and slay (once again)
their owners, or is there a swifter path?

==============================================================

caigoshinobi@freyja:~$ ./PWN-VOYAGE_L3 a
caigoshinobi@freyja:~$

```

So without arguments, the executable seems to simply print the banner. When providing an argument, the behavior is different, but it doesn't return anything useful.


Let's analyze the decompiled binary:

```

int __fastcall main(int argc, const char **argv, const char **envp)
{
  char v4; // bl
  char v5; // [rsp+19h] [rbp-4D7h] BYREF
  char v6; // [rsp+1Ah] [rbp-4D6h]
  char v7; // [rsp+1Bh] [rbp-4D5h]
  unsigned int v8; // [rsp+1Ch] [rbp-4D4h]
  int i; // [rsp+20h] [rbp-4D0h]
  int v10; // [rsp+24h] [rbp-4CCh]
  char *s; // [rsp+28h] [rbp-4C8h]
  char v12[1035]; // [rsp+30h] [rbp-4C0h] BYREF
  char v13; // [rsp+43Bh] [rbp-B5h] BYREF
  char dest[4]; // [rsp+43Ch] [rbp-B4h] BYREF
  char s2[48]; // [rsp+440h] [rbp-B0h] BYREF
  char v16[8]; // [rsp+470h] [rbp-80h] BYREF
  __int64 v17; // [rsp+478h] [rbp-78h]
  __int64 v18; // [rsp+480h] [rbp-70h]
  __int64 v19; // [rsp+488h] [rbp-68h]
  __int64 v20; // [rsp+490h] [rbp-60h]
  __int64 v21; // [rsp+498h] [rbp-58h]
  __int64 v22; // [rsp+4A0h] [rbp-50h]
  __int64 v23; // [rsp+4A8h] [rbp-48h]
  __int64 v24; // [rsp+4B0h] [rbp-40h]
  __int64 v25; // [rsp+4B8h] [rbp-38h]
  __int64 v26; // [rsp+4C0h] [rbp-30h]
  __int64 v27; // [rsp+4C8h] [rbp-28h]
  int v28; // [rsp+4D0h] [rbp-20h]
  unsigned __int64 v29; // [rsp+4D8h] [rbp-18h]

  v29 = __readfsqword(0x28u);
  level_check();
  if ( argc == 2 )
  {
    s = (char *)argv[1];
    v10 = strlen(s);
    *(_QWORD *)v16 = 0LL;
    v17 = 0LL;
    v18 = 0LL;
    v19 = 0LL;
    v20 = 0LL;
    v21 = 0LL;
    v22 = 0LL;
    v23 = 0LL;
    v24 = 0LL;
    v25 = 0LL;
    v26 = 0LL;
    v27 = 0LL;
    v28 = 0;
    v8 = 0;
    v6 = 1;
    for ( i = 0; i < v10; i += 3 )
    {
      strncpy(dest, &s[i], 3uLL);
      dest[3] = 0;
      calculate_hash(dest, (__int64)s2);
      if ( v8 > 0x18 )
      {
        v6 = 0;
        break;
      }
      if ( strcmp((&mapping)[2 * (int)v8], s2) )
      {
        v6 = 0;
        break;
      }
      v7 = atoi(dest);
      v13 = v7;
      RC4_set_key(v12, 1LL, &v13);
      RC4(v12, 1LL, &(&mapping)[2 * (int)v8 + 1], &v5);
      v4 = v5;
      v16[strlen(v16)] = v4;
      ++v8;
    }
    v16[v8] = 0;
    if ( v6 )
    {
      puts(v16);
      return 0;
    }
    else
    {
      return 1;
    }
  }
  else
  {
    banner();
    return 0;
  }
}


```

A quick analysis:

- It accepts command-line arguments (`argc` and `argv`).

- The `level_check()` function is called at the start, to control the presence of the previous flags.

- The program checks the value of `argc`. If there are exactly two command-line arguments, the program proceeds with processing. Otherwise, it displays a banner and exits with a success status.

- The second argument (`argv[1]`) is stored in the variable `s`.

- The length of `s` is calculated and stored in the variable `v10`.

- We have a `for` loop that iterates through the string `s` every three characters. In each iteration, it extracts three characters from `s` and stores them in the `dest` variable.

- `dest` is used as input for the `calculate_hash` function, which produces a result in the `s2` variable.

- The numeric value of `dest` is converted to `v7`, which is then used to initialize a key for the RC4 algorithm (`RC4_set_key`). The RC4 algorithm is applied to the input with the specified key, and the result is stored in `v4`.

- We also note that if `s2` does not match the value in `(&mapping)[2 * (int)v8]`, `v6` is set to 0, and the loop is terminated.


So the `main` function appears to read a sequence strings from `s`, calculate hashes for each string, and then decrypt the data using the RC4 algorithm. If all operations are completed successfully, the result is printed. However, any errors or deviations in the operations will result in an exit with an error state.


...but where is this mapping? In various decompilers, there is no trace of it.


Let's now revisit our previously found MD5 hashes and paste some of them to CrackStation, which can't hurt.


| Hash                                | Type     | Results          |
|-------------------------------------|----------|------------------|
| 202cb962ac59075b964b07152d234b70    | MD5      | 123  |
| ec8956637a99787bd197eacd77acce5e    | MD5      | 102  |
| b73ce398c39f506af761d2277d853a92    | MD5      | 160  |
| 5737034557ef5b8c02c0e46513b98f90    | MD5      | 539  |
| a2557a7b2e94197ff767970b67041697    | MD5      | 189  |
| d1f491a404d6854880943e5c3cd9ca25    | MD5      | 129  |
| c75b6f114c23a4d7ea11331e7c00e73c    | MD5      | 547  |

...and so on. But wait. In the previous for loop, weren't 3 characters being processed at each iteration?

```

caigoshinobi@freyja:~$./PWN-VOYAGE_L3 123102160539189129547
NTRLGC{

```

Let's go. 

```

m@freyja:/mnt/c/Users/matca/Desktop/CTF/GPV001/GAME$ ./PWN-VOYAGE_L3 123102160539189129547466101140987766222105984456102937578380986134730596111
NTRLGC{1MBRUT30RSCH0L4R?}

```

As the flag said, there is also the *brute* way:


```

import subprocess

def execute_command(argument):
    process = subprocess.Popen(["./PWN-VOYAGE_L3", argument], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    stdout, stderr = process.communicate()
    return stdout

def main():
    argument = "000"
    while True:
        output = execute_command(argument)
        if output:
            print(f"./PWN-VOYAGE_L3 {argument} -> {output.strip()}")
            for i in range(1000):
                new_argument = argument + f"{i:03d}"
                new_output = execute_command(new_argument)
                if new_output:
                    argument = new_argument
                    break
            else:
                break
        else:
            argument = f"{int(argument) + 1:03d}"

if __name__ == "__main__":
    main()
	
```

```

m@freyja:/mnt/c/Users/matca/Desktop/CTF/GPV001/GAME$ python3 imbrute.py
./PWN-VOYAGE_L3 123 -> N
./PWN-VOYAGE_L3 123102 -> NT
./PWN-VOYAGE_L3 123102160 -> NTR
./PWN-VOYAGE_L3 123102160539 -> NTRL
./PWN-VOYAGE_L3 123102160539189 -> NTRLG
./PWN-VOYAGE_L3 123102160539189129 -> NTRLGC
./PWN-VOYAGE_L3 123102160539189129547 -> NTRLGC{
./PWN-VOYAGE_L3 123102160539189129547466 -> NTRLGC{1
./PWN-VOYAGE_L3 123102160539189129547466101 -> NTRLGC{1M
./PWN-VOYAGE_L3 123102160539189129547466101140 -> NTRLGC{1MB
./PWN-VOYAGE_L3 123102160539189129547466101140987 -> NTRLGC{1MBR
./PWN-VOYAGE_L3 123102160539189129547466101140987766 -> NTRLGC{1MBRU
./PWN-VOYAGE_L3 123102160539189129547466101140987766222 -> NTRLGC{1MBRUT
./PWN-VOYAGE_L3 123102160539189129547466101140987766222105 -> NTRLGC{1MBRUT3
./PWN-VOYAGE_L3 123102160539189129547466101140987766222105984 -> NTRLGC{1MBRUT30
./PWN-VOYAGE_L3 123102160539189129547466101140987766222105984456 -> NTRLGC{1MBRUT30R
./PWN-VOYAGE_L3 123102160539189129547466101140987766222105984456102 -> NTRLGC{1MBRUT30RS
./PWN-VOYAGE_L3 123102160539189129547466101140987766222105984456102937 -> NTRLGC{1MBRUT30RSC
./PWN-VOYAGE_L3 123102160539189129547466101140987766222105984456102937578 -> NTRLGC{1MBRUT30RSCH
./PWN-VOYAGE_L3 123102160539189129547466101140987766222105984456102937578380 -> NTRLGC{1MBRUT30RSCH0
./PWN-VOYAGE_L3 123102160539189129547466101140987766222105984456102937578380986 -> NTRLGC{1MBRUT30RSCH0L
./PWN-VOYAGE_L3 123102160539189129547466101140987766222105984456102937578380986134 -> NTRLGC{1MBRUT30RSCH0L4
./PWN-VOYAGE_L3 123102160539189129547466101140987766222105984456102937578380986134730 -> NTRLGC{1MBRUT30RSCH0L4R
./PWN-VOYAGE_L3 123102160539189129547466101140987766222105984456102937578380986134730596 -> NTRLGC{1MBRUT30RSCH0L4R?
./PWN-VOYAGE_L3 123102160539189129547466101140987766222105984456102937578380986134730596111 -> NTRLGC{1MBRUT30RSCH0L4R?}

```