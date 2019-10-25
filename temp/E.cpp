#include <gmp.h>
#include <stdio.h>

int main(){
  mpf_set_default_prec(200);

  mpf_t sum;
  mpf_init(sum);
  mpf_set_ui(sum,0);
  unsigned int i = 0;

  for (int i=0; i<1000; i++) {
    mpf_t cur;
    mpf_init(cur);
    mpf_set_ui(cur, 1);

    for (int j=1; j<=i; j++) {
        mpf_div_ui(cur, cur, (unsigned long)(j));
    }
    mpf_add(sum, sum, cur);
  }
  

  mpf_out_str(stdout,10, 100, sum);
  printf ("\n");
  mpf_clear(sum);
}
