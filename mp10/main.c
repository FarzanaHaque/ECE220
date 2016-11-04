
#include <stdio.h>


#include "cmp_mat.h"
#ifndef SP_MAT
#define SP_MAT
#include "sparsemat.h"
#endif

int main(int argc, char *argv[]){

    if(argc > 2){
        printf("Too many arguments.\n");
        return 0;
    }
    
    if (argc == 2){
        int s = atoi(argv[1]);
        switch (s){
            case 1:
                printf("Test 1: tuple functions\n");
                goto TEST_1;
                break;
            default:
                printf("Error: Valid arguments are 1-3");
                return 0;
        }        
        printf("%s\n",argv[1]);
    }


	TEST_1:printf("calling load_tuples on \"matrices/input_mats/scrambled_rows.txt\":\n");
	sp_tuples * unscrambledrowst = load_tuples("matrices/input_mats/scrambled_rows.txt");
	printt(unscrambledrowst);
	
	printf("calling load_tuples on \"matrices/input_mats/withZeroes.txt\":\n");
	sp_tuples * withZeroest = load_tuples("matrices/input_mats/withZeroes.txt");
	printt(withZeroest);
	
	sp_tuples * a_At = load_tuples("matrices/input_mats/a_A.txt");
	sp_tuples * a_Bt = load_tuples("matrices/input_mats/a_B.txt");
	printf("a_Ct = a_A+a_B addition in tuples:\n");
	sp_tuples * a_Ct = add_tuples(a_At,a_Bt);
	printt(a_Ct);
	
	sp_tuples * sa_At = load_tuples("matrices/input_mats/sa_A.txt");
	sp_tuples * sa_Bt = load_tuples("matrices/input_mats/sa_B.txt");
	printf("sa_Ct = sa_A+sa_B sparse addition in tuples:\n");
	sp_tuples * sa_Ct = add_tuples(sa_At,sa_Bt);
	printt(sa_Ct);
	
	sp_tuples * m_At = load_tuples("matrices/input_mats/m_A.txt");
	sp_tuples * m_Bt = load_tuples("matrices/input_mats/m_B.txt");
	printf("m_Ct = m_A*m_B multiplication in tuples:\n");
	sp_tuples * m_Ct = mult_tuples(m_At,m_Bt);
	printt(m_Ct);
	
	sp_tuples * sm_At = load_tuples("matrices/input_mats/sm_A.txt");
	sp_tuples * sm_Bt = load_tuples("matrices/input_mats/sm_B.txt");
	printf("sm_Ct = sm_A*sm_B sparse multiplication in tuples:\n");
	sp_tuples * sm_Ct = mult_tuples(sm_At,sm_Bt);
	printt(sm_Ct);
	
	printf("Saving output matrices... \n");
	
	save_tuples("matrices/output_mats/withZeroest.txt",withZeroest);
	save_tuples("matrices/output_mats/unscrambled.txt",unscrambledrowst);
	save_tuples("matrices/output_mats/a_Ct.txt",a_Ct);
	save_tuples("matrices/output_mats/sa_Ct.txt",sa_Ct);
	save_tuples("matrices/output_mats/m_Ct.txt",m_Ct);
	save_tuples("matrices/output_mats/sm_Ct.txt",sm_Ct);
	
    printf("freeing matrices from memory..\n");
	destroy_tuples(withZeroest);
	destroy_tuples(unscrambledrowst);
	destroy_tuples(a_At);
	destroy_tuples(sa_At);
	destroy_tuples(m_At);
	destroy_tuples(sm_At);
	
	
	destroy_tuples(a_Bt);
	destroy_tuples(sa_Bt);
	destroy_tuples(m_Bt);
	destroy_tuples(sm_Bt);
	
	destroy_tuples(a_Ct);
	destroy_tuples(sa_Ct);
	destroy_tuples(m_Ct);
	destroy_tuples(sm_Ct);
	

    return 0;
}
