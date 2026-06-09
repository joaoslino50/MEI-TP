#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#define SHA256_BLOCK_SIZE 64
#define SHA256_DIGEST_SIZE 32

// SHA256 context structure
typedef struct {
    uint8_t data[SHA256_BLOCK_SIZE];
    uint32_t datalen;
    uint64_t bitlen;
    uint32_t state[8];
} SHA256_CTX;

// Base64URL character set
const char base64url_alphabet[] = 
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";

// SHA256 functions
uint32_t sha256_k[] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
    0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
    0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
    0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
    0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
    0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

uint32_t sha256_ror(uint32_t x, int n) {
    return (x >> n) | (x << (32 - n));
}

uint32_t sha256_ch(uint32_t x, uint32_t y, uint32_t z) {
    return (x & y) ^ (~x & z);
}

uint32_t sha256_maj(uint32_t x, uint32_t y, uint32_t z) {
    return (x & y) ^ (x & z) ^ (y & z);
}

uint32_t sha256_bsig0(uint32_t x) {
    return sha256_ror(x, 2) ^ sha256_ror(x, 13) ^ sha256_ror(x, 22);
}

uint32_t sha256_bsig1(uint32_t x) {
    return sha256_ror(x, 6) ^ sha256_ror(x, 11) ^ sha256_ror(x, 25);
}

uint32_t sha256_ssig0(uint32_t x) {
    return sha256_ror(x, 7) ^ sha256_ror(x, 18) ^ (x >> 3);
}

uint32_t sha256_ssig1(uint32_t x) {
    return sha256_ror(x, 17) ^ sha256_ror(x, 19) ^ (x >> 10);
}

void sha256_transform(SHA256_CTX *ctx) {
    uint32_t w[64];
    uint32_t i, j;
    uint32_t t1, t2;
    uint32_t a, b, c, d, e, f, g, h;
    
    for (i = 0; i < 16; i++) {
        w[i] = (ctx->data[i * 4] << 24) | (ctx->data[i * 4 + 1] << 16) |
               (ctx->data[i * 4 + 2] << 8) | (ctx->data[i * 4 + 3]);
    }
    
    for (i = 16; i < 64; i++) {
        w[i] = sha256_ssig1(w[i - 2]) + w[i - 7] + sha256_ssig0(w[i - 15]) + w[i - 16];
    }
    
    a = ctx->state[0];
    b = ctx->state[1];
    c = ctx->state[2];
    d = ctx->state[3];
    e = ctx->state[4];
    f = ctx->state[5];
    g = ctx->state[6];
    h = ctx->state[7];
    
    for (i = 0; i < 64; i++) {
        t1 = h + sha256_bsig1(e) + sha256_ch(e, f, g) + sha256_k[i] + w[i];
        t2 = sha256_bsig0(a) + sha256_maj(a, b, c);
        h = g;
        g = f;
        f = e;
        e = d + t1;
        d = c;
        c = b;
        b = a;
        a = t1 + t2;
    }
    
    ctx->state[0] += a;
    ctx->state[1] += b;
    ctx->state[2] += c;
    ctx->state[3] += d;
    ctx->state[4] += e;
    ctx->state[5] += f;
    ctx->state[6] += g;
    ctx->state[7] += h;
}

void sha256_init(SHA256_CTX *ctx) {
    ctx->datalen = 0;
    ctx->bitlen = 0;
    ctx->state[0] = 0x6a09e667;
    ctx->state[1] = 0xbb67ae85;
    ctx->state[2] = 0x3c6ef372;
    ctx->state[3] = 0xa54ff53a;
    ctx->state[4] = 0x510e527f;
    ctx->state[5] = 0x9b05688c;
    ctx->state[6] = 0x1f83d9ab;
    ctx->state[7] = 0x5be0cd19;
}

void sha256_update(SHA256_CTX *ctx, const uint8_t *data, size_t len) {
    for (size_t i = 0; i < len; i++) {
        ctx->data[ctx->datalen] = data[i];
        ctx->datalen++;
        if (ctx->datalen == SHA256_BLOCK_SIZE) {
            sha256_transform(ctx);
            ctx->bitlen += SHA256_BLOCK_SIZE * 8;
            ctx->datalen = 0;
        }
    }
}

void sha256_final(SHA256_CTX *ctx, uint8_t *hash) {
    size_t i = ctx->datalen;
    
    if (ctx->datalen < 56) {
        ctx->data[i++] = 0x80;
        while (i < 56) {
            ctx->data[i++] = 0x00;
        }
    } else {
        ctx->data[i++] = 0x80;
        while (i < SHA256_BLOCK_SIZE) {
            ctx->data[i++] = 0x00;
        }
        sha256_transform(ctx);
        memset(ctx->data, 0, 56);
    }
    
    ctx->bitlen += ctx->datalen * 8;
    ctx->data[56] = (ctx->bitlen >> 56) & 0xFF;
    ctx->data[57] = (ctx->bitlen >> 48) & 0xFF;
    ctx->data[58] = (ctx->bitlen >> 40) & 0xFF;
    ctx->data[59] = (ctx->bitlen >> 32) & 0xFF;
    ctx->data[60] = (ctx->bitlen >> 24) & 0xFF;
    ctx->data[61] = (ctx->bitlen >> 16) & 0xFF;
    ctx->data[62] = (ctx->bitlen >> 8) & 0xFF;
    ctx->data[63] = (ctx->bitlen) & 0xFF;
    
    sha256_transform(ctx);
    
    for (i = 0; i < 4; i++) {
        hash[i * 4] = (ctx->state[i] >> 24) & 0xFF;
        hash[i * 4 + 1] = (ctx->state[i] >> 16) & 0xFF;
        hash[i * 4 + 2] = (ctx->state[i] >> 8) & 0xFF;
        hash[i * 4 + 3] = ctx->state[i] & 0xFF;
    }
}

void sha256(const uint8_t *data, size_t len, uint8_t *hash) {
    SHA256_CTX ctx;
    sha256_init(&ctx);
    sha256_update(&ctx, data, len);
    sha256_final(&ctx, hash);
}

// HMAC-SHA256 implementation
void hmac_sha256(const uint8_t *key, size_t key_len, 
                 const uint8_t *message, size_t msg_len, 
                 uint8_t *hmac) {
    uint8_t k_ipad[SHA256_BLOCK_SIZE];
    uint8_t k_opad[SHA256_BLOCK_SIZE];
    uint8_t inner_hash[SHA256_DIGEST_SIZE];
    uint8_t key_buf[SHA256_BLOCK_SIZE];
    SHA256_CTX ctx;
    
    memset(key_buf, 0, SHA256_BLOCK_SIZE);
    if (key_len > SHA256_BLOCK_SIZE) {
        sha256(key, key_len, key_buf);
        memcpy(key_buf, key_buf, SHA256_DIGEST_SIZE);
    } else {
        memcpy(key_buf, key, key_len);
    }
    
    for (int i = 0; i < SHA256_BLOCK_SIZE; i++) {
        k_ipad[i] = key_buf[i] ^ 0x36;
        k_opad[i] = key_buf[i] ^ 0x5c;
    }
    
    sha256_init(&ctx);
    sha256_update(&ctx, k_ipad, SHA256_BLOCK_SIZE);
    sha256_update(&ctx, message, msg_len);
    sha256_final(&ctx, inner_hash);
    
    sha256_init(&ctx);
    sha256_update(&ctx, k_opad, SHA256_BLOCK_SIZE);
    sha256_update(&ctx, inner_hash, SHA256_DIGEST_SIZE);
    sha256_final(&ctx, hmac);
}

// Base64URL encoding
char* base64url_encode(const uint8_t *input, size_t len) {
    size_t output_len = ((len + 2) / 3) * 4;
    char *output = malloc(output_len + 1);
    
    size_t i = 0, j = 0;
    while (i < len) {
        uint32_t octet_a = i < len ? input[i++] : 0;
        uint32_t octet_b = i < len ? input[i++] : 0;
        uint32_t octet_c = i < len ? input[i++] : 0;
        
        uint32_t triple = (octet_a << 16) | (octet_b << 8) | octet_c;
        
        output[j++] = base64url_alphabet[(triple >> 18) & 0x3F];
        output[j++] = base64url_alphabet[(triple >> 12) & 0x3F];
        output[j++] = base64url_alphabet[(triple >> 6) & 0x3F];
        output[j++] = base64url_alphabet[triple & 0x3F];
    }
    
    // Remove padding for URL-safe
    size_t pad = (3 - (len % 3)) % 3;
    output_len -= pad;
    output[output_len] = '\0';
    
    return output;
}

// Helper: string to uint8_t array
size_t str_to_uint8(const char *str, uint8_t **out) {
    size_t len = strlen(str);
    *out = malloc(len);
    memcpy(*out, str, len);
    return len;
}

// Create JWT token
char* create_jwt(const char *header, const char *payload, const char *secret) {
    uint8_t *header_bytes, *payload_bytes;
    size_t header_len = str_to_uint8(header, &header_bytes);
    size_t payload_len = str_to_uint8(payload, &payload_bytes);
    
    char *header_b64 = base64url_encode(header_bytes, header_len);
    char *payload_b64 = base64url_encode(payload_bytes, payload_len);
    
    free(header_bytes);
    free(payload_bytes);
    
    size_t signature_input_len = strlen(header_b64) + 1 + strlen(payload_b64);
    char *signature_input = malloc(signature_input_len + 1);
    sprintf(signature_input, "%s.%s", header_b64, payload_b64);
    
    uint8_t *secret_bytes;
    size_t secret_len = str_to_uint8(secret, &secret_bytes);
    
    uint8_t signature[SHA256_DIGEST_SIZE];
    hmac_sha256(secret_bytes, secret_len, 
                (uint8_t*)signature_input, signature_input_len, 
                signature);
    
    free(secret_bytes);
    free(signature_input);
    
    char *signature_b64 = base64url_encode(signature, SHA256_DIGEST_SIZE);
    
    size_t token_len = strlen(header_b64) + 1 + strlen(payload_b64) + 1 + strlen(signature_b64);
    char *token = malloc(token_len + 1);
    sprintf(token, "%s.%s.%s", header_b64, payload_b64, signature_b64);
    
    free(header_b64);
    free(payload_b64);
    free(signature_b64);
    
    return token;
}

// Verify JWT token
int verify_jwt(const char *token, const char *secret) {
    char token_copy[512];
    strcpy(token_copy, token);
    
    char *part1 = strtok(token_copy, ".");
    char *part2 = strtok(NULL, ".");
    char *part3 = strtok(NULL, ".");
    
    if (!part1 || !part2 || !part3) {
        return 0;
    }
    
    size_t signature_input_len = strlen(part1) + 1 + strlen(part2);
    char *signature_input = malloc(signature_input_len + 1);
    sprintf(signature_input, "%s.%s", part1, part2);
    
    uint8_t *secret_bytes;
    size_t secret_len = str_to_uint8(secret, &secret_bytes);
    
    uint8_t computed_signature[SHA256_DIGEST_SIZE];
    hmac_sha256(secret_bytes, secret_len,
                (uint8_t*)signature_input, signature_input_len,
                computed_signature);
    
    free(secret_bytes);
    free(signature_input);
    
    char *computed_b64 = base64url_encode(computed_signature, SHA256_DIGEST_SIZE);
    
    int valid = (strcmp(part3, computed_b64) == 0);
    
    free(computed_b64);
    return valid;
}

int main() {
    const char *header = "{\"alg\":\"HS256\",\"typ\":\"JWT\"}";
    const char *payload = "{\"sub\":\"1234567890\",\"name\":\"John Doe\",\"iat\":1516239022}";
    const char *secret = "mySecretKey";
    
    char *token = create_jwt(header, payload, secret);
    printf("Generated JWT Token:\n%s\n\n", token);
    
    int valid = verify_jwt(token, secret);
    printf("Verification result: %s\n", valid ? "VALID ✓" : "INVALID ✗");
    
    // Test with wrong secret
    printf("\nTesting with wrong secret:\n");
    valid = verify_jwt(token, "wrongSecret");
    printf("Verification result: %s\n", valid ? "VALID ✓" : "INVALID ✗");
    
    free(token);
    
    return 0;
}