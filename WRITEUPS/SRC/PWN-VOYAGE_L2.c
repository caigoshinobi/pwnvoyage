#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/bio.h>

//gcc PWN-VOYAGE_L2.c -o PWN-VOYAGE_L2 -lssl -lcrypto -fno-stack-protector -s

void demonic_things(const unsigned char *input, const char *key, unsigned char *output, size_t length) {
    size_t key_len = strlen(key);
    for (size_t i = 0; i < length; i++) {
        output[i] = input[i] ^ key[i % key_len];
    }
}

void door_broken(const char *pick) {
    const char *lock = "000000000000001C7B7D1F78737D181005001F6D2E";
    unsigned char decoded[128];
    int len = strlen(lock) / 2;

    for (int i = 0; i < len; i++) {
        sscanf(&lock[i * 2], "%02hhX", &decoded[i]);
    }

    unsigned char decrypted[128];
    memset(decrypted, 0, sizeof(decrypted));
    demonic_things(decoded, pick, decrypted, len);
	printf("\n");
    printf("-$> Flag: %s\n", decrypted);
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

int level_check(const char *level1_flag) {
    const char *input_flag = level1_flag;

    const char *level1_hash = "57f9da0be0924d42c69f4d9dce38bb76";
    
    EVP_MD_CTX *mdctx;
    const EVP_MD *md = EVP_md5();
    unsigned char md_value[EVP_MAX_MD_SIZE];
    unsigned int md_len;
    
    mdctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(mdctx, md, NULL);
    EVP_DigestUpdate(mdctx, input_flag, strlen(input_flag));
    EVP_DigestFinal_ex(mdctx, md_value, &md_len);
    EVP_MD_CTX_free(mdctx);
    
    char calculated_hash[33];
    
    for (unsigned int i = 0; i < md_len; i++) {
        sprintf(&calculated_hash[i * 2], "%02x", md_value[i]);
    }
        
    if (strcmp(calculated_hash, level1_hash) == 0) {
        printf("-$> Access Granted. Now let's pwn this f*cking door\n");
		printf("\n");
        return 1;
    } else {
        incorrect_flag(1);
        return 0;
    }
}

void banner() {
	printf("\n"
	   "============================================================ \n"
	   "                                                             \n"
	   " ██▓    ▓█████ ██▒   █▓▓█████  ██▓           ██▓ ██▓         \n"
	   "▓██▒    ▓█   ▀▓██░   █▒▓█   ▀ ▓██▒          ▓██▒▓██▒         \n"
	   "▒██░    ▒███   ▓██  █▒░▒███   ▒██░          ▒██▒▒██▒         \n"
	   "▒██░    ▒▓█  ▄  ▒██ █░░▒▓█  ▄ ▒██░          ░██░░██░         \n"
	   "░██████▒░▒████▒  ▒▀█░  ░▒████▒░██████▒      ░██░░██░         \n"
	   "░ ▒░▓  ░░░ ▒░ ░  ░ ▐░  ░░ ▒░ ░░ ▒░▓  ░      ░▓  ░▓           \n"
	   "░ ░ ▒  ░ ░ ░  ░  ░ ░░   ░ ░  ░░ ░ ▒  ░       ▒ ░ ▒ ░         \n"
	   "  ░ ░      ░       ░░     ░     ░ ░          ▒ ░ ▒ ░         \n"
	   "====░==░===░==░=====░=====░==░====░==░=======░===░========== \n"
	   "                    ░                                        \n"
	   "You mercilessly annihilate a pair of bloodthirsty undead,    \n"
	   "their pitiable forms disintegrating in the face of your      \n"
	   "power. However, as you reach the very threshold of the Vault,\n"
	   "a discouraging sight awaits you: The Vault's door is veiled  \n"
	   "in an enigmatic magical aura, a barrier challenging anyone   \n"
	   "to enter... yet you charge ahead with all your might.        \n"
	   "                                                             \n"
	   "============================================================ \n"
	   "\n");
}

int main(int argc, char *argv[]) {
	banner();
    char buffer[128];
    int i;

	char door_status[] = "CLOSED";
    FILE *input_file = fopen("FLAG.txt", "r");
    if (!input_file) {
        file_required();
        return 1;
    }

    char controller[256];
    fread(controller, sizeof(char), 300, input_file);
    fclose(input_file);
    controller[33] = '\0';

    if (level_check(controller)) {
		printf("-$> You give an almighty shove. The door is now %s\n", door_status);

		if (strstr(door_status, "OPEN") != NULL) {
			FILE *input_file = fopen("FLAG.txt", "r");
			if (!input_file) {
				file_required();
				return 1;
			}
			char snado[300];
			fread(snado, sizeof(char), 300, input_file);
			fclose(input_file);
			door_broken(snado);
			return 0;
		} else {
			printf("\n"
			       "-$> You are hurled backward by a spell from the ancient gates, compelled    \n"
			       "    to retreat a few paces. The curses of defense begin to graze your armor,\n"
			       "    slowly dissolving the metal. Yet, the voice of your conscience continues\n"
			       "    to echo just one thing: Keep pushing.\n"
			       "\n");
			return 1;
		}
	}
}


