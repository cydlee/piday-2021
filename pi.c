#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <gmp.h>

#define DEFAULT_PI_DIGITS 10
#define MAX_PI_DIGITS 1000000

static int help_flag;

int main (int argc, char *argv[])
{
	unsigned long int digits = DEFAULT_PI_DIGITS;

	// Option parsing
	//-----------------------------------------------------------------------------------
	int c;
	char *dvalue = NULL;

	while (1)
	{
		static struct option long_options[] =
		{
			{"help", no_argument, &help_flag, 1},
		};

		int option_index = 0;

		c = getopt_long (argc, argv, "d:", long_options, &option_index);

		if (c == -1)
			break;

		switch (c)
		{
			case 0:
				break;
			case 'd':
				dvalue = optarg;
				char *ep;
				digits = strtoul (dvalue, &ep, 0);
				if (digits > MAX_PI_DIGITS)
					digits = MAX_PI_DIGITS;
				break;
			case '?':
				break;
			default:
				abort ();
		}
	}

	if (help_flag)
	{
		printf ("Usage: pi [OPTION]...\n");
		printf ("Calculates the value of pi (rounded).\n");
		printf ("\n");
		printf ("  -d <digits>    Specify the number of decimal places to calculate. Default is %d, maximum is %d.\n", DEFAULT_PI_DIGITS, MAX_PI_DIGITS);
		printf ("      --help     Display this help message and exit.\n");
		return 0;
	}

	// Pi calculator code
	//-----------------------------------------------------------------------------------
	unsigned long int denom_a, denom_b, denom_c, denom_d;

	mpf_set_default_prec (1000000);

	mpf_t one;
	mpf_t two;
	mpf_t four;
	mpf_t sixteen;

	mpf_t pi;       // Value of pi
	mpf_t product;  // Product of 1/16^k and (fractions) to add to pi each iteration
	mpf_t sum;      // Sum of fractions
	mpf_t frac_exp; // Fraction 1/16^k
	mpf_t exp;      // Denominator 16^k
	mpf_t frac_a;   // 1st fraction
	mpf_t frac_b;   // 2nd fraction
	mpf_t frac_c;   // 3rd fraction
	mpf_t frac_d;   // 4th fraction

	mpf_init (one);
	mpf_init (two);
	mpf_init (four);
	mpf_init (sixteen);

	mpf_init (pi);
	mpf_init (product);
	mpf_init (sum);
	mpf_init (frac_exp);
	mpf_init (exp);
	mpf_init (frac_a);
	mpf_init (frac_b);
	mpf_init (frac_c);
	mpf_init (frac_d);

	mpf_set_d (one, 1);
	mpf_set_d (two, 2);
	mpf_set_d (four, 4);
	mpf_set_d (sixteen, 16);

	for (unsigned long int k = 0; k < digits; k++)
	{
		mpf_pow_ui (exp, sixteen, k);
		mpf_div (frac_exp, one, exp);

		denom_a = (8 * k) + 1;
		denom_b = (8 * k) + 4;
		denom_c = (8 * k) + 5;
		denom_d = (8 * k) + 6;
		
		mpf_div_ui (frac_a, four, denom_a);
		mpf_div_ui (frac_b, two, denom_b);
		mpf_div_ui (frac_c, one, denom_c);
		mpf_div_ui (frac_d, one, denom_d);

		mpf_sub (sum, frac_a, frac_b);
		mpf_sub (sum, sum, frac_c);
		mpf_sub (sum, sum, frac_d);

		mpf_mul (product, frac_exp, sum);

		mpf_add (pi, pi, product);
	}

	gmp_printf ("PI = %.*Ff\n", digits, pi);

	mpf_clear (one);
	mpf_clear (two);
	mpf_clear (four);
	mpf_clear (sixteen);

	mpf_clear (pi);
	mpf_clear (product);
	mpf_clear (sum);
	mpf_clear (frac_exp);
	mpf_clear (exp);
	mpf_clear (frac_a);
	mpf_clear (frac_b);
	mpf_clear (frac_c);
	mpf_clear (frac_d);

	return 0;
}
