#include<stdio.h>
//max length for line or column
#define MD 100

//max number of rules
#define MR 52

//check rule is respected on a line
int check_rule_line(int line, int rule, int M, int model[MD][MD], int *start)
{
	//check the bounds
	if (*start + rule - 1 > M)
		return 0;

	//if a white square is met, the rule is not respected
	for (int i = *start; i < *start + rule; i++)
		if (!model[line][i])
			return 0;
	//the length of the black squares sequence should not exceed the length forced by the rule
	if (model[line][*start + rule] && *start + rule < M)
		return 0;

	//moving over the found black squares
	*start += rule;
	return 1;
}

//same as previous but for column
int check_rule_column(int col, int rule, int N, int model[MD][MD], int *start)
{
	if (*start + rule - 1 > N)
		return 0;
	for (int i = *start; i < *start + rule; i++)
		if (!model[i][col])
			return 0;
	if (model[*start + rule][col] && *start + rule < N)
		return 0;
	*start += rule;
	return 1;
}

//check a whole line
int check_line(int M, int line, int model[MD][MD], int rules_N[MD][MR])
{
	int line_position = 0;
	for (int i = 1; i <= rules_N[line][0]; i++) {
		while (!model[line][line_position] && line_position < M)
			line_position++;

		//moving over white squares
		if (!check_rule_line(line, rules_N[line][i], M, model, &line_position))
			return 0;
	}

	return 1;
}


//same as previous but for column
int check_column(int N, int col, int model[MD][MD], int rules_M[MD][MR])
{
	int col_position = 0;
	for (int i = 1; i <= rules_M[col][0]; i++) {
		while (!model[col_position][col] && col_position < N)
			col_position++;
		if (!check_rule_column(col, rules_M[col][i], N, model, &col_position))
			return 0;
	}

	return 1;
}

//check all lines and column
int full_check(int N, int M, int model[MD][MD], int rules_N[MD][MR],
			   int rules_M[MD][MR])
{
	for (int i = 0; i < N ; i++)
		if (!check_line(M, i, model, rules_N))
			return 0;
	for (int i = 0; i < M; i++)
		if (!check_column(N, i, model, rules_M))
			return 0;
	return 1;
}

//check one model
void main_algorithm(void)
{
	int N, M, i, j;
	scanf("%d%d", &N, &M);
	int rules_N[MD][MR], rules_M[MD][MR], model[MD][MD];

	//register rules for lines
	for (i = 0; i < N; i++) {
		scanf("%d", &rules_N[i][0]);
		for (j = 1; j <= rules_N[i][0]; j++)
			scanf("%d", &rules_N[i][j]);

	}

	//register rules for column
	for (i = 0; i < M; i++) {
		scanf("%d", &rules_M[i][0]);
		for (j = 1; j <= rules_M[i][0]; j++)
			scanf("%d", &rules_M[i][j]);

	}

	for (i = 0; i < N; i++)
		for (j = 0; j < M; j++)
			scanf("%d", &model[i][j]);

	//reading the model
	if (full_check(N, M, model, rules_N, rules_M))
		printf("Corect\n");
	else
		printf("Eroare\n");
}

int main(void)
{
	int T;
	scanf("%d", &T);

	//repeat for all models
	for (int i = 0; i < T; i++)
		main_algorithm();
	return 0;
}
