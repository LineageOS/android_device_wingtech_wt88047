/*
 * Copyright (C) 2015 The CyanogenMod Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <openssl/evp.h>

#define EVP_CIPH_RAND_KEY		0x200

#define EVP_F_EVP_OPENINIT				 	102
#define EVP_R_PUBLIC_KEY_NOT_RSA			106
#define EVP_F_EVP_PKEY_ENCRYPT_OLD			152

#define EVPerr(f,r)  void

int		EVP_PKEY_decrypt_old(unsigned char *dec_key,
			const unsigned char *enc_key,int enc_key_len,
			EVP_PKEY *private_key);
int		EVP_PKEY_encrypt_old(unsigned char *enc_key,
			const unsigned char *key,int key_len,
			EVP_PKEY *pub_key);
