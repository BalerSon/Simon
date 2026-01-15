define rounds 32;

__in bit key[64];
__in bit pt[32];

__out bit ct[32];

bit z0[32] = 0xb386a45f;
bit c[16] = 0xfffc;

bit round_keys[rounds][16];


void key_schedule()
{
	int i;
	
	for (i = 0; i < 16; i = i + 1)
	{
		round_keys[0][i] = key[i];
		round_keys[1][i] = key[16 + i];
		round_keys[2][i] = key[32 + i];
		round_keys[3][i]= key[48 + i];
	}
	
	int j;
	for (j = 4; j < rounds; j = j + 1)
	{
		__mem bit tmp[16] = (round_keys[j - 1] <<< 3) ^ round_keys[j - 3];
		tmp = tmp ^ (tmp <<< 1);
		
		bit z_bit = z0[j - 4];
		round_keys[j] = round_keys[j - 4] ^ tmp ^ c;
		round_keys[j][0] = round_keys[j][0] ^ z_bit;
	}
}

void encrypt()
{
	bit left[16];
	bit right[16];
	int i;
	
	for (i = 0; i < 16; i = i + 1)
	{
		left[i] = pt[16 + i];
		right[i] = pt[i];
	}
	
	int j;
	for (j = 0; j < rounds; j = j + 1)
	{
		bit tmp[16] = left;
		left = ((left >>> 1) & (left >>> 8)) ^ (left >>> 2);
		left = left ^ right ^ round_keys[j];
		right = tmp;
	}
	
	int k;
	for (k = 0; k < 16; k = k + 1)
	{
		ct[k] = right[k];
		ct[16 + k] = left[k];
	}
}


void main()
{
	key_schedule();
	encrypt();
}