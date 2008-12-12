/*
 * Seahorse
 *
 * Copyright (C) 2003 Jacob Perkins
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the
 * Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef __SEAHORSE_PGP_KEY_OP_H__
#define __SEAHORSE_PGP_KEY_OP_H__

#include <glib.h>
#include <gpgme.h>
#include <time.h>

#include "seahorse-operation.h"

#include "pgp/seahorse-gpgmex.h"
#include "pgp/seahorse-pgp-key.h"
#include "pgp/seahorse-pgp-subkey.h"
#include "pgp/seahorse-pgp-uid.h"
#include "pgp/seahorse-pgp-photo.h"
#include "pgp/seahorse-pgp-source.h"

/* Key type options. */
typedef enum {
	/* DSA key with ElGamal subkey. The DSA key will have length of 1024,
	 * while the ElGamal length is variable within #ELGAMAL_MIN and
	 * #LENGTH_MAX. Only used in seahorse_ops_key_generate().
	 */
	DSA_ELGAMAL = 1,
	/* DSA key, sign only. Can be a subkey or a primary key.
	 * See #DSA_MIN and #DSA_MAX.
	 */
	DSA = 2,
	/* ElGamal subkey, encrypt only. See #ELGAMAL_MIN and #LENGTH_MAX.
	 * Only used in seahorse_ops_key_add_subkey().
	 */
	ELGAMAL = 4,
	/* RSA key, sign only. Can be a subkey or a primary key.
	 * See #RSA_MIN and #RSA_MAX.
	 */
	RSA_SIGN = 5,
	/* RSA subkey, encrypt only. See #RSA_MIN and #RSA_MAX.
	 * Only used in seahorse_ops_key_add_subkey().
	 */
	RSA_ENCRYPT = 6
} SeahorseKeyEncType;

/* Length ranges for key types */
typedef enum {
	/* Minimum length for #DSA. */
	DSA_MIN = 768,
	/* Maximum length for #DSA. */
	DSA_MAX = 1024,
	/* Minimum length for #ELGAMAL. Maximum length is #LENGTH_MAX. */
	ELGAMAL_MIN = 768,
	/* Minimum length of #RSA_SIGN and #RSA_ENCRYPT. Maximum length is
	 * #LENGTH_MAX.
	 */
	RSA_MIN = 1024,
	/* Maximum length for #ELGAMAL, #RSA_SIGN, and #RSA_ENCRYPT. */
	LENGTH_MAX = 4096
} SeahorseKeyLength;

typedef enum {
	/* Unknown key check */
	SIGN_CHECK_NO_ANSWER,
	/* Key not checked */
	SIGN_CHECK_NONE,
	/* Key casually checked */
	SIGN_CHECK_CASUAL,
	/* Key carefully checked */
	SIGN_CHECK_CAREFUL
} SeahorseSignCheck;

typedef enum {
	/* If signature is local */
	SIGN_LOCAL = 1 << 0,
	/* If signature is non-revocable */
	SIGN_NO_REVOKE = 1 << 1,
	/* If signature expires with key */
	SIGN_EXPIRES = 1 << 2
} SeahorseSignOptions;

typedef enum {
	/* No revocation reason */
	REVOKE_NO_REASON = 0,
	/* Key compromised */
	REVOKE_COMPROMISED = 1,
	/* Key replaced */
	REVOKE_SUPERSEDED = 2,
	/* Key no longer used */
	REVOKE_NOT_USED = 3
} SeahorseRevokeReason;

SeahorseOperation*    seahorse_pgp_key_op_generate           (SeahorsePGPSource  *sksrc,
                                                              const gchar *name,
                                                              const gchar *email,
                                                              const gchar *comment,
                                                              const gchar *passphrase,
                                                              SeahorseKeyEncType type,
                                                              guint length,
                                                              time_t expires,
                                                              gpgme_error_t *err);

gpgme_error_t         seahorse_pgp_key_op_delete             (SeahorsePgpKey *pkey);

gpgme_error_t         seahorse_pgp_key_op_delete_pair        (SeahorsePgpKey *pkey);

gpgme_error_t         seahorse_pgp_key_op_sign               (SeahorsePgpKey *key,
                                                              SeahorsePgpKey *signer,
                                                              SeahorseSignCheck check,
                                                              SeahorseSignOptions options);

gpgme_error_t         seahorse_pgp_key_op_sign_uid           (SeahorsePgpUid *uid, 
                                                              SeahorsePgpKey *signer, 
                                                              SeahorseSignCheck check, 
                                                              SeahorseSignOptions options);

gpgme_error_t         seahorse_pgp_key_op_change_pass        (SeahorsePgpKey *pkey);

gpgme_error_t         seahorse_pgp_key_op_set_trust          (SeahorsePgpKey *pkey,
                                                              SeahorseValidity validity);

gpgme_error_t         seahorse_pgp_key_op_set_disabled       (SeahorsePgpKey *pkey,
                                                              gboolean disabled);

gpgme_error_t         seahorse_pgp_key_op_set_expires        (SeahorsePgpSubkey *subkey,
                                                              time_t expires);

gpgme_error_t         seahorse_pgp_key_op_add_revoker        (SeahorsePgpKey *pkey, 
                                                              SeahorsePgpKey *revoker);

gpgme_error_t         seahorse_pgp_key_op_add_uid            (SeahorsePgpKey *pkey,
                                                              const gchar *name,
                                                              const gchar *email,
                                                              const gchar *comment);

gpgme_error_t         seahorse_pgp_key_op_primary_uid        (SeahorsePgpUid *uid);

gpgme_error_t         seahorse_pgp_key_op_del_uid            (SeahorsePgpUid *uid);
                             
gpgme_error_t         seahorse_pgp_key_op_add_subkey         (SeahorsePgpKey *pkey,
                                                              SeahorseKeyEncType type,
                                                              guint length,
                                                              time_t expires);

gpgme_error_t         seahorse_pgp_key_op_del_subkey         (SeahorsePgpSubkey *subkey);

gpgme_error_t         seahorse_pgp_key_op_revoke_subkey      (SeahorsePgpSubkey *subkey,
                                                              SeahorseRevokeReason reason,
                                                              const gchar *description);

gpgme_error_t         seahorse_pgp_key_op_photo_add          (SeahorsePgpKey *pkey,
                                                              const gchar *filename);
 
gpgme_error_t         seahorse_pgp_key_op_photo_delete       (SeahorsePgpPhoto *photo);
                                                     
gpgme_error_t         seahorse_pgp_key_op_photos_load        (SeahorsePgpKey *key);

gpgme_error_t         seahorse_pgp_key_op_photo_primary      (SeahorsePgpPhoto *photo);

#endif /* __SEAHORSE_PGP_KEY_OP_H__ */
