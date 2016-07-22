#ifndef LOWMC_PARS_H
#define LOWMC_PARS_H

#include "m4ri/m4ri.h" 

/**
 * Represents the LowMC parameters as in https://bitbucket.org/malb/lowmc-helib/src,
 * with the difference that key is a two dimensional array to allow for secret shared
 * keys 
 */
typedef struct {
  size_t m;
  size_t n;
  size_t r;
  size_t k;
  mzd_t **key;
  mzd_t **LMatrix;
  mzd_t **KMatrix;
  mzd_t **Constants;
  
} lowmc_t;

/**
 * Samples the L matrix for the LowMC instance
 *
 * \param n the blocksize
 */
mzd_t *mzd_sample_lmatrix(rci_t n);

/**
 * Samples the K matrix for the LowMC instance
 * \param n the blocksize
 */
mzd_t *mzd_sample_kmatrix(rci_t n, rci_t k);

/**
 * Generates a new LowMC instance (also including a key)
 * 
 * \param m the number of sboxes
 * \param n the blocksize
 * \param r the number of rounds
 * \param k the keysize
 *
 * \return parameters defining a LowMC instance (including a key)
 */
lowmc_t *lowmc_init(size_t m, size_t n, size_t r, size_t k);

/**
 * Frees the allocated LowMC parameters
 * 
 * \param lowmc the LowMC parameters to be freed
 */
void lowmc_free(lowmc_t *lowmc);

/**
 * Updates a given LowMC parameter instance so that the key is 
 * split into three components representing the additive secret 
 * sharing of LowMC
 * 
 * \param lowmc the LowMC parameters
 */
void lowmc_secret_share(lowmc_t *lowmc);

#endif
