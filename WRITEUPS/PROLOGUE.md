# PWNVOYAGE / SPECIAL / PROLOGUE

Here we have some fallen and damaged signposts. 
Running the level without arguments, we see a list of signposts (note that they start from II) with some words in uppercase.

```

caigoshinobi@freyja:~$ ./PWN-VOYAGE_PROLOGUE

=====================================================================

 ██▓███   ██▀███   ▒█████   ██▓     ▒█████    ▄████  █    ██ ▓█████
▓██░  ██▒▓██ ▒ ██▒▒██▒  ██▒▓██▒    ▒██▒  ██▒ ██▒ ▀█▒ ██  ▓██▒▓█   ▀
▓██░ ██▓▒▓██ ░▄█ ▒▒██░  ██▒▒██░    ▒██░  ██▒▒██░▄▄▄░▓██  ▒██░▒███
▒██▄█▓▒ ▒▒██▀▀█▄  ▒██   ██░▒██░    ▒██   ██░░▓█  ██▓▓▓█  ░██░▒▓█  ▄
▒██▒ ░  ░░██▓ ▒██▒░ ████▓▒░░██████▒░ ████▓▒░░▒▓███▀▒▒▒█████▓ ░▒████▒
▒▓▒░ ░  ░░ ▒▓ ░▒▓░░ ▒░▒░▒░ ░ ▒░▓  ░░ ▒░▒░▒░  ░▒   ▒ ░▒▓▒ ▒ ▒ ░░ ▒░ ░
░▒ ░       ░▒ ░ ▒░  ░ ▒ ▒░ ░ ░ ▒  ░  ░ ▒ ▒░   ░   ░ ░░▒░ ░ ░  ░ ░  ░
░░         ░░   ░ ░ ░ ░ ▒    ░ ░   ░ ░ ░ ▒  ░ ░   ░  ░░░ ░ ░    ░
            ░         ░ ░      ░  ░    ░ ░        ░    ░        ░  ░

You have long forsaken the well-trodden paths of farmers and herders,
yet the road to the Vault remains distant. The route you are pursuing
appears abandoned for decades, overgrown with brambles. At last, you
come across a few signposts, haphazardly arranged upon an ancient
dead tree. Some seem fallen, making it challenging to discern the
direction to take.

=====================================================================

-$> Signpost:

    II   YOUNG Shadows Inn
    III  Mystic Tor TO Darkness
    IV   Everglow DIE Woods
    V    Eldermist BRO Hold

-$> Choose the right path to proceed:

```

Running the `strings` command on the executable, we find the first signpost:

```

caigoshinobi@freyja:~$ strings PWN-VOYAGE_PROLOGUE | grep signpost
come across a few signposts, haphazardly arranged upon an ancient
signpost
I_signpost_TOO_SpineChilling_Manor

```

By stringing together the uppercase words from the various signposts in order, we obtain: **TOOYOUNGTODIEBRO**
so...

```

-$> Signpost:

    II   YOUNG Shadows Inn
    III  Mystic Tor TO Darkness
    IV   Everglow DIE Woods
    V    Eldermist BRO Hold

-$> Choose the right path to proceed: TOOYOUNGTODIEBRO

-$> So, you've got: PRLG{HURT_M3_PL3NTY}

```

There's no need to go into too much detail on this challenge; however, we can say that through examining the file, we see that the binary is not stripped.

```

caigoshinobi@freyja:~$ file PWN-VOYAGE_PROLOGUE
PWN-VOYAGE_PROLOGUE: ELF 64-bit LSB pie executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, BuildID[sha1]=e4d3733da734817be2f902709cdc4274d534dfc8, for GNU/Linux 3.2.0, not stripped

```

From a quick analysis, we discover that a simple XOR operation is performed between the input string and the flag. 
With the correct string, the flag is decrypted. If an incorrect string is entered, the knight takes a wrong path.

```

-$> Signpost:

    II   YOUNG Shadows Inn
    III  Mystic Tor TO Darkness
    IV   Everglow DIE Woods
    V    Eldermist BRO Hold

-$> Choose the right path to proceed: TEST123

-$> So, you've got: PXPJ/(AEC]K(!J9IO'

```



