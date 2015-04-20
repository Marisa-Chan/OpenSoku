#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char * tex[256];

int main(int argc, char *argv[])
{
    memset(tex,0,256*sizeof(char *));

    FILE *f = fopen(argv[1],"rb");

    int32_t tmp;

    fread(&tmp,4,1,f);
    fread(&tmp,4,1,f);

    for (int32_t i=0; i < tmp; i++)
    {
        int32_t ln;
        fread(&ln,4,1,f);

        tex[i] = (char *)calloc(ln+1,1);
        fread(tex[i],ln,1,f);

        fread(&ln,4,1,f);
        fread(&ln,4,1,f);
        fread(&ln,4,1,f);
        fread(&ln,4,1,f);

        //printf("%s\n",tex[i]);
    }

    fread(&tmp,4,1,f);

    for (int32_t i=0; i < tmp; i++)
    {
        int32_t guide;
        int8_t type;

        fread(&guide,4,1,f);
        fread(&type,1,1,f);

        printf("Guid %5.1d    ", guide);

        switch(type)
        {
        case 0:
        case 2:
        case 3:
        case 4:
        case 5:
        {
            if (type == 0)
                printf("CDesignSprite\n");
            else
                printf("CDesignGage %d\n", type - 2);
            int32_t tid, x, y, invert;
            fread(&tid,4,1,f);
            fread(&x,4,1,f);
            fread(&y,4,1,f);
            fread(&invert,4,1,f);
            printf("\t%s\n\tx %d  y %d  invert %d\n",tex[tid],x,y,invert);
        }
        break;

        case 1:
        {
            printf("CDesignObjectBase\n");
            int32_t x, y;
            fread(&x,4,1,f);
            fread(&y,4,1,f);
            printf("\tx %d  y %d\n",x,y);
        }
        break;

        case 6:
        {
            printf("CDesignNumber\n");
            int32_t tid, w, h, x, y, frames, dw, intg, flt;
            fread(&tid,4,1,f);
            fread(&x,4,1,f);
            fread(&y,4,1,f);
            fread(&w,4,1,f);
            fread(&h,4,1,f);
            fread(&frames,4,1,f);
            fread(&dw,4,1,f);
            fread(&intg,4,1,f);
            fread(&flt,4,1,f);
            printf("\t%s\n\tx %d  y %d  w %d  h %d  frames %d  spacing %d  int %d  float %d\n",tex[tid],x,y,w,h,frames,dw,intg,flt);
        }
        break;

        default:
            break;
        }
        printf("\n");
    }

    fclose(f);

    return 0;
}
