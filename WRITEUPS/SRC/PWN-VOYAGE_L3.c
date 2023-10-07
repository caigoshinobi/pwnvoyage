#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/rc4.h>

//gcc PWN-VOYAGE_L3.c -o PWN-VOYAGE_L3 -lssl -lcrypto

typedef struct {
    const char *hash;
    char letter;
} CodeLetter;

CodeLetter mapping[] = {
	{"202cb962ac59075b964b07152d234b70", 0x92}, //123
	{"ec8956637a99787bd197eacd77acce5e", 0x04}, //102
	{"b73ce398c39f506af761d2277d853a92", 0x00}, //160
	{"5737034557ef5b8c02c0e46513b98f90", 0x7b}, //539
	{"a2557a7b2e94197ff767970b67041697", 0x28}, //189
	{"d1f491a404d6854880943e5c3cd9ca25", 0xe9}, //129
	{"c75b6f114c23a4d7ea11331e7c00e73c", 0x22}, //547
	{"e836d813fd184325132fca8edcdfb40e", 0xee}, //466
	{"38b3eff8baf56627478ec76a704e9b52", 0x8c}, //101
	{"1385974ed5904a438616ff7bdb3f7439", 0xf2}, //140
	{"df6d2338b2b8fce1ec2f6dda0a630eb0", 0x25}, //987
	{"959a557f5f6beb411fd954f3f34b21c3", 0x66}, //766
	{"bcbe3365e6ac95ea2c0343a2395834dd", 0x8f}, //222
	{"65b9eea6e1cc6bb9f0cd2a47751a186f", 0xfb}, //105
	{"d93ed5b6db83be78efb0d05ae420158e", 0x1e}, //984
	{"250cf8b51c773f3f8dc8b4be867a9a02", 0xb6}, //456
	{"ec8956637a99787bd197eacd77acce5e", 0x03}, //102
	{"b7892fb3c2f009c65f686f6355c895b5", 0x03}, //937
	{"a8849b052492b5106526b2331e526138", 0x5d}, //578
	{"bca82e41ee7b0833588399b1fcd177c7", 0x28}, //380
	{"fe7ee8fc1959cc7214fa21c4840dff0a", 0x0c}, //986
	{"02522a2b2726fb0a03bb19f2d8d9524d", 0x36}, //134
	{"d5cfead94f5350c12c322b5b664544c1", 0x12}, //730
	{"b2eeb7362ef83deff5c7813a67e14f0a", 0xfd}, //596
	{"698d51a19d8a121ce581499d7b701668", 0x86}  //111
};

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

void level_check() {
	
    const char *level_hashes[] = {
        "57f9da0be0924d42c69f4d9dce38bb76",
        "53399b5bea2489071870f825e5ca61ac"
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

void banner() {
	printf("\n"
	   "============================================================== \n"
	   "                                                               \n"
	   " ██▓    ▓█████ ██▒   █▓▓█████  ██▓           ██▓ ██▓ ██▓       \n"
	   "▓██▒    ▓█   ▀▓██░   █▒▓█   ▀ ▓██▒          ▓██▓▓██▓▓██▒       \n"
	   "▒██░    ▒███   ▓██  █▒░▒███   ▒██░          ▒██▒▒██▒▒██▒       \n"
	   "▒██░    ▒▓█  ▄  ▒██ █░░▒▓█  ▄ ▒██░          ░██░░██░░██░       \n"
	   "░██████▒░▒████▒  ▒▀█░  ░▒████▒░██████▒      ░██░░██░░██░       \n"
	   "░ ▒░▓  ░░░ ▒░ ░  ░ ▐░  ░░ ▒░ ░░ ▒░▓  ░      ░▓  ░▓  ░▓         \n"
	   "░ ░ ▒  ░ ░ ░  ░  ░ ░░   ░ ░  ░░ ░ ▒  ░       ▒ ░ ▒ ░ ▒         \n"
	   "  ░ ░      ░       ░░     ░     ░ ░          ▒   ▒ ░ ▒ ░       \n"
	   "====░==░===░==░=====░=====░==░====░==░=======░===░===░======== \n"
	   "                    ░                                          \n"
	   "Finally within the Vault, you cast your gaze around. The Sword \n"
	   "of Heroes must lie within one of these tombs. Yet, you are well\n"
	   "aware that guarding the sword is Grimshade, a legendary Wraith \n"
	   "and its last owner. The Vault, however, houses dozens of tombs \n"
	   "(and undeads). Shall you open them all and slay (once again)   \n"
	   "their owners, or is there a swifter path?                      \n"
	   "                                                               \n"
	   "============================================================== \n"
	   "\n");
}

int main(int argc, char *argv[]) {
	level_check();
    if (argc != 2) {
		banner();
        return 0;
    }

    char *input_sequence = argv[1];
    int sequence_length = strlen(input_sequence);
    char stringvalid[100] = "";
    int valid_index = 0;
    bool valid_sequence = true;
    char hash_str[33];
    
    for (int i = 0; i < sequence_length; i += 3) {
        char code_str[4];
        strncpy(code_str, input_sequence + i, 3);
        code_str[3] = '\0';
        
        calculate_hash(code_str, hash_str);

        if (valid_index >= sizeof(mapping) / sizeof(mapping[0])) {
            valid_sequence = false;
            break;
        }

		if (strcmp(mapping[valid_index].hash, hash_str) == 0) {
			RC4_KEY rc4_key;
			unsigned char key_value = (unsigned char)atoi(code_str);
			unsigned char key_byte_array[] = { key_value };
			RC4_set_key(&rc4_key, sizeof(key_byte_array), key_byte_array);
			unsigned char decrypted_byte;
			RC4(&rc4_key, 1, &mapping[valid_index].letter, &decrypted_byte);
			stringvalid[strlen(stringvalid)] = decrypted_byte;
			valid_index++;
		} else {
			valid_sequence = false;
			break;
		}
    }
    
    stringvalid[valid_index] = '\0';

    if (valid_sequence) {
        printf("%s\n", stringvalid);
    } else {
        return 1;
    }

    return 0;
}


