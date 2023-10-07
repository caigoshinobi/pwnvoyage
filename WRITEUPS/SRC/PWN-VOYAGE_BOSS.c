#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <openssl/evp.h>

//gcc PWN-VOYAGE_BOSS.c -o PWN-VOYAGE_BOSS -lssl -lcrypto -s

int skeletons_cab(int x) {
    int operations[] = {2, 3, 1, 2, 4};
    int var1 = 5, var2 = 2, var3 = 1, var4 = 4, var5 = 8, var6 = 6, var7 = 4;

    for (int i = 0; i < 5; i++) {
        x += operations[i];
		x += (var6++, var3);
        x += var1 - var2;
		x -= (var7--, var3);
    }

    return x;
}

int skeletons_cac(int y) {
    int operations[] = {3, 2, 4, 1, 2};
    int var1 = 10, var2 = 3, var3 = 3, var4 = 4;

    for (int i = 0; i < 5; i++, var3++, var4--) {
        y *= operations[i];
        y += var1;
        y /= var2;
    }

    return y;
}

int skeletons_cad(int z) {
    int operations[] = {1, 2, 3, 1, 4};
    int var1 = 8, var2 = 4, var5 = 200, var6 = 6;

    for (int i = 0; i < 5; i++, var5++, var6--) {
        z -= operations[i];
        z *= var1;
        z += var2;
    }

    return z;
}

int skeletons_cae(int f) {
    int operations[] = {4, 3, 2, 4, 1};
    int var1 = 7, var2 = 5, var6 = 3, var7 = 1;

    for (int i = 0; i < 5; i++, var7++, var6--) {
        f /= operations[i];
        f -= var1;
        f *= var2;
    }

    return f;
}

int skeletons_caa() {
    int varskeletons_cab = skeletons_cab(2);
    int varskeletons_cac = skeletons_cac(varskeletons_cab);
    int varskeletons_cad = skeletons_cad(varskeletons_cac);
    int varskeletons_cae = skeletons_cae(varskeletons_cad);

    return varskeletons_cae + 220;
}

int skeletons_can() {
    int varskeletons_cab = skeletons_cab(8);
    int varskeletons_cac = skeletons_cac(varskeletons_cab);
    int varskeletons_cad = skeletons_cad(varskeletons_cac);
    int varskeletons_cae = skeletons_cae(varskeletons_cad);

    return varskeletons_cae + 120;
}

int skeletons_cao() {
    int varskeletons_cab = skeletons_cab(4);
    int varskeletons_cac = skeletons_cac(varskeletons_cab);
    int varskeletons_cad = skeletons_cad(varskeletons_cac);
    int varskeletons_cae = skeletons_cae(varskeletons_cad);
    return varskeletons_cae + 154;
}

int skeletons_caz() {
	int r = skeletons_caa();
	int d = skeletons_can();
	int c = skeletons_cao();
	return r + d + c;
}

void demonic_things(const char *xor_encrypted_hex, int xor_key) {
    size_t xor_length = strlen(xor_encrypted_hex) / 2;
    unsigned char xor_encrypted[xor_length];
    unsigned char xor_decrypted[xor_length + 2];

    for (size_t i = 0; i < xor_length; i++) {
        sscanf(xor_encrypted_hex + i * 2, "%2hhx", &xor_encrypted[i]);
    }

    for (size_t i = 0; i < xor_length; i++) {
        xor_decrypted[i] = xor_encrypted[i] ^ xor_key;
    }
	
    xor_decrypted[xor_length] = '\0';
    printf("-$> Flag: %s\n", xor_decrypted);
	printf("\n");
}

void file_required() {
	printf("\n"
		   "------------------------------------------------------\n"
		   "| *FLAG.txt REQUIRED*                                |\n"
		   "|                                                    |\n"
		   "| Create the FLAG.txt file and insert the flags of   |\n"
		   "| the previous levels, one per line.                 |\n"
		   "------------------------------------------------------\n"
		   "\n");
}

void incorrect_flag(int flag) {
	printf("\n"
		   "------------------------------------------------------\n"
		   "| *INCORRECT FLAG.txt ENTRY*                         |\n"
		   "|                                                    |\n"
		   "| Incorrect FLAG for level %d. Please review the      |\n"
		   "| FLAG.txt file.                                     |\n"
		   "------------------------------------------------------\n"
		   "\n", flag);
}

void trim_string(char *str) {
	int len = strlen(str);
	while (len > 0 && isspace((unsigned char)str[len - 1])) {
		len--;
	}
	str[len] = '\0';

	while (*str && isspace((unsigned char)*str)) {
		str++;
	}
}

int calculate_hash(const char *input, char *output) {
	EVP_MD_CTX *mdctx;
	const EVP_MD *md;
	unsigned char md_value[EVP_MAX_MD_SIZE];
	unsigned int md_len;

	OpenSSL_add_all_digests();
	md = EVP_get_digestbyname("md5");
	if (md == NULL) {
		fprintf(stderr, "ERR");
		return 0;
	}

	mdctx = EVP_MD_CTX_new();
	EVP_DigestInit_ex(mdctx, md, NULL);
	EVP_DigestUpdate(mdctx, input, strlen(input));
	EVP_DigestFinal_ex(mdctx, md_value, &md_len);
	EVP_MD_CTX_free(mdctx);

	for (int i = 0; i < md_len; i++) {
		snprintf(output + i*2, 3, "%02x", md_value[i]);
	}
	
	return 1;
}

void level_check() {
	
    const char *level_hashes[] = {
        "57f9da0be0924d42c69f4d9dce38bb76",
        "53399b5bea2489071870f825e5ca61ac",
        "868501a250db98b7b1a2ef0ad1856f4b"
    };
	
	int num_levels = sizeof(level_hashes) / sizeof(level_hashes[0]);
	
    FILE *file = fopen("FLAG.txt", "r");
    if (file == NULL) {
        file_required();
        exit(1);
    }

    char buffers[num_levels][60];
    char md5_hashes[num_levels][33];

    for (int i = 0; i < num_levels; ++i) {
        if (fgets(buffers[i], sizeof(buffers[i]), file) == NULL) {
            incorrect_flag(i+1);
            fclose(file);
            exit(1);
        }
        trim_string(buffers[i]);
        calculate_hash(buffers[i], md5_hashes[i]);		
        if (strcmp(md5_hashes[i], level_hashes[i]) != 0) {
            incorrect_flag(i+1);
            fclose(file);
            exit(1);
        }
    }
    fclose(file);
}

int chandelier_rope(int min, int max) {
    return min + rand() % (max - min + 1);
}

int death() {
	printf("\n"
		   "-$> Grimshade emerges victorious, his malevolent power overwhelming. The Sword\n" 
		   "    of Heroes finds its mark multiple times upon thee, each strike a chilling\n"
		   "    reminder of your vulnerability. As the battle's outcome becomes clear, an\n"
		   "    unbreakable fate is woven – to stand as a guardian of the Vault for all \n"
		   "    eternity, an unliving sentinel in service to its ancient secrets.\n"
		   "\n"
		   "-$> I know... so sad. You are dead\n"
		   "\n");
	return 1;
}

void banner() {
	printf("\n"
	       "========================================================================== \n"
	       "                                                                           \n"
	       " ▄▄▄▄    ▒█████    ██████   ██████      █████▒██▓  ▄████  ██░ ██ ▄▄▄█████▓ \n"
	       "▓█████▄ ▒██▒  ██▒▒██    ▒ ▒██    ▒    ▓██   ▒▓██▒ ██▒ ▀█▒▓██░ ██▒▓  ██▒ ▓▒ \n"
	       "▒██▒ ▄██▒██░  ██▒░ ▓██▄   ░ ▓██▄      ▒████ ░▒██▒▒██░▄▄▄░▒██▀▀██░▒ ▓██░ ▒░ \n"
	       "▒██░█▀  ▒██   ██░  ▒   ██▒  ▒   ██▒   ░▓█▒  ░░██░░▓█  ██▓░▓█ ░██ ░ ▓██▓ ░  \n"
	       "░▓█  ▀█▓░ ████▓▒░▒██████▒▒▒██████▒▒   ░▒█░   ░██░░▒▓███▀▒░▓█▒░██▓  ▒██▒ ░  \n"
	       "░▒▓███▀▒░ ▒░▒░▒░ ▒ ▒▓▒ ▒ ░▒ ▒▓▒ ▒ ░    ▒ ░   ░▓   ░▒   ▒  ▒ ░░▒░▒  ▒ ░░    \n"
	       "▒░▒   ░   ░ ▒ ▒░ ░ ░▒  ░ ░░ ░▒  ░ ░    ░      ▒ ░  ░   ░  ▒ ░▒░ ░    ░     \n"
	       " ░    ░ ░ ░ ░ ▒  ░  ░  ░  ░  ░  ░      ░ ░    ▒ ░░ ░   ░  ░  ░░ ░  ░       \n"
	       " ░          ░ ░        ░        ░             ░        ░  ░  ░  ░          \n"
	       "      ░                                                                    \n"
	       "Finally, the tomb of Grimshade hath been unsealed! The Vault is shrouded   \n"
	       "in an ominous mist. The Wraith hovers through the chamber, its gaze fixed  \n"
	       "upon you, while its legendary blade sways with an eerie rhythm. For a      \n"
	       "brief moment, the two lock eyes, each assessing the other's essence. At    \n"
	       "last, the grand clash commences, a spectacle of power and fate intertwined.\n"
	       "                                                                           \n"
	       "========================================================================== \n"
	       "\n");
}

int main() {
	level_check();
	banner();
    srand(time(NULL));
    int mkHP = 50;
    int grimshadeHP = 255;
    printf("-$> Defeat Grimshade!\n");

    while (mkHP > 0 && grimshadeHP != 0) {
		printf("\n");
		printf("|------------------------\n");
        printf("| KNIGHT        HP:  %d  \n", mkHP);
        printf("| GRIMSHADE     HP:  %d  \n", grimshadeHP);
	    printf("|------------------------\n");
        int mkAttack = chandelier_rope(5, 15);
        int GrimshadeAttack = chandelier_rope(5, 15);
		printf("\n");
        printf("Press a key to continue...\n");
        getchar();
        printf("-$> You deal %d damage to Grimshade!\n", mkAttack);
        grimshadeHP -= mkAttack;
        printf("-$> Grimshade inflicts %d damage on you!\n", GrimshadeAttack);
        mkHP -= GrimshadeAttack;
    }

    if (grimshadeHP == 0) {
		const char *xor_encrypted_hex = "E2F8FEE0EBEFD7F89CF3EE9FF3EF9CE29B9DE2F99FE88D84E198F5EE9F85D1";
		int skeletons_caz_output = skeletons_caz();
        printf("\n"
           "-$> A skilled knight possesses, alongside sheer strength, a healthy dose of cunning.\n"
           "    You choose not to succumb to the immense power of the Wraith. With a skillful\n"
           "    sword swing, you cut the rope that holds a heavy chandelier attached to the crypt's\n"
           "    ceiling. Grimshade is impaled and trapped by the mass of iron, allowing you to finish\n"
           "    him off with two final strikes. Finally, you grasp the Sword of Heroes, a long-sought\n"
           "    and greatly desired weapon. A blade that, furthermore, is essential for the Main Adventure\n"
           "    that awaits you! \n"
           "\n");
        demonic_things(xor_encrypted_hex, skeletons_caz_output);
    } else {
		death();
    }
    return 0;
}

