#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DRAW_MAX 50

#define CARD_MAX 3

typedef struct Card Card;

struct Card {
	int nums[25];
	int flags[25];
};



struct Range {
	int begin,end;
} ranges[5] = { {1,15}, {16,30}, {31,45}, {46,60}, {61,75} };



char *patterns[] = {

	"11111"
	"00000"
	"00000"
	"00000"
	"00000",

	"00000"
	"11111"
	"00000"
	"00000"
	"00000",

	"00000"
	"00000"
	"11111"
	"00000"
	"00000",

	"00000"
	"00000"
	"00000"
	"11111"
	"00000",

	"00000"
	"00000"
	"00000"
	"00000"
	"11111",

	"10000"
	"10000"
	"10000"
	"10000"
	"10000",


	"01000"
	"01000"
	"01000"
	"01000"
	"01000",

	"00100"
	"00100"
	"00100"
	"00100"
	"00100",

	"00010"
	"00010"
	"00010"
	"00010"
	"00010",

	"00001"
	"00001"
	"00001"
	"00001"
	"00001",

	"10000"
	"01000"
	"00100"
	"00010"
	"00001",

	"00001"
	"00010"
	"00100"
	"01000"
	"10000",

	"11111"
	"11111"
	"11111"
	"11111"
	"11111",
};

int npatterns=13;



double drand() {
	return rand()/(RAND_MAX+1.0);
}



int *shuffle(int *c,int n) {
	int i,j,k;
	for(i=n-1;i>0;i--) {
		j=rand()%(i+1);
		k=c[i];
		c[i]=c[j];
		c[j]=k;
	}
	return c;
}



int *Column_New(int b,int e,int c) {
	int i,j=0;
	int min=0,max=e-b+1;
	int r=max;
	int n=c;
	int *d=malloc(sizeof(int)*n);
	for(i=min;i<=max;i++) {
		if(((double)n/r)>=drand()) {
			d[j++]=i+b;
			n--;
		}
		r--;
	}

	return shuffle(d,5);
}



Card *Card_New() {
	Card *card=malloc(sizeof(Card)*25);
	int *k;
	int i,j;

	for(i=0;i<25;i++) {
		card->flags[i]=0;
	}

	for(i=0;i<5;i++) {
		k=Column_New(
			ranges[i].begin,
			ranges[i].end,
			5
		);
		for(j=0;j<5;j++) {
			card->nums[i+j*5]=k[j];
		}
		free(k);
	}
	return card;
}


void Card_Free(void *card) {
	free(card);
}


void Card_Print(Card *card) {
	int i,j,k;
	printf("%s\n","   B    I    N    G    O   ");
	for(j=0;j<5;j++) {
		for(i=0;i<5;i++) {
			k=i+j*5;
			if(card->flags[k]) printf(" (%2d)",card->nums[k]);
			else printf("  %2d ",card->nums[k]);
		}
		printf("\n");
	}
	printf("\n");
}


int Card_Win(Card *c,char **p,int n) {
	int i,j;
	for(j=0;j<n;j++) {
		int m=1;
		for(i=0;i<25;i++) {
			if(!c->flags[i] && p[j][i]=='1') {
				m=0;
				break;
			}
		}
		if(m) return 1;
	}
	return 0;
}


int main(void) {

	Card *cards[CARD_MAX];

	int *d=calloc(75,sizeof(int));

	int i,j,k;

	int w;



	srand(time(NULL));

	for(i=0;i<CARD_MAX;i++) {
		cards[i]=Card_New();
	}

	for(i=0;i<75;i++) {
		d[i]=i+1;
	}

	shuffle(d,75);

	printf("Drawn: ");
	for(i=0;i<DRAW_MAX;i++) {
		if(i!=0) printf(" ");
		printf("%d",d[i]);
	}
	printf("\n\n");


	w=0;
	for(k=0;k<CARD_MAX;k++) {

		for(j=0;j<DRAW_MAX;j++) {
			for(i=0;i<25;i++) {
				if(cards[k]->nums[i]==d[j]) cards[k]->flags[i]=1;
      }
		}

	}

	for(i=0;i<CARD_MAX;i++) {
		Card_Print(cards[i]);
	}

	for(i=0;i<CARD_MAX;i++) {
		if(Card_Win(cards[i],patterns,npatterns)) {
			w=1;
			break;
		}
	}

	if(w) {
		printf("You Win!");
	} else {
		printf("You Lose!");
	}

	for(i=0;i<CARD_MAX;i++) {
		Card_Free(cards[i]);
	}

	return 0;
}


