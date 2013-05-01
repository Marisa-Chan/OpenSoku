#include "global_types.h"
#include "archive.h"
#include "file_read.h"
#include "cards.h"
#include "text.h"

s_cards *cards_common = NULL;

bool cards_load_cards(s_cards *cards, const char *charname)
{
    //For begin we will load common cards
    if (!cards_common)
    {
        cards_common = new s_cards;
        cards_load_cards(cards_common,"common");
    }

    if (!cards->cards_holder.empty())
    {
        cards->cards_holder.clear();
        cards->card_mapping.clear();
    }

    char buf[CHRBUF];

    sprintf(buf, "data/csv/%s/spellcard.cv1", charname);

    filehandle *f = arc_get_file(buf);

    if (!f)
        return false;

    char * txt = txt_load_cv1(f);

    uint32_t txtsz = f->get_size();

    delete f;

    uint32_t off = 0;
    uint32_t oldoff = 0;
    uint32_t period = 0;

    while (off < txtsz)
    {
        off++;
        if (off >= txtsz || txt[off] == 0xA || txt[off] == 0)
        {
            if (period == 14)
            {
                strncpy(buf, txt + oldoff, off - oldoff);
                char *nxt = strtok(buf,",");
                s_card tmp;
                tmp.id = atoi(nxt);

                nxt = strtok(NULL,",");
                strcpy(tmp.name, nxt);

                nxt = strtok(NULL,",");
                tmp.type = atoi(nxt);

                nxt = strtok(NULL,",");
                tmp.cost = atoi(nxt);

                nxt = strtok(NULL,",");
                strcpy(tmp.description, nxt);

                nxt = strtok(NULL,",");
                tmp.stage = atoi(nxt);

                nxt = strtok(NULL,",");
                tmp.rare = atoi(nxt);

                nxt = strtok(NULL,",");
                tmp.p7 = atoi(nxt);

                nxt = strtok(NULL,",");
                tmp.p8 = atoi(nxt);

                nxt = strtok(NULL,",");
                tmp.p9 = atoi(nxt);

                nxt = strtok(NULL,",");
                tmp.p10 = atoi(nxt);

                nxt = strtok(NULL,",");
                tmp.p11 = atoi(nxt);

                nxt = strtok(NULL,",");
                tmp.p12 = atoi(nxt);

                nxt = strtok(NULL,",");
                tmp.p13 = atoi(nxt);

                nxt = strtok(NULL,",");
                tmp.sort = atoi(nxt);

                char buf2[CHRBUF];
                sprintf(buf2,"data/card/%s/card%03d.cv2",charname, tmp.id);

                filehandle *ft = arc_get_file(buf2);
                if (!ft)
                    tmp.tex = NULL;
                else
                {
                    tmp.tex = gr_load_cv2(ft, NULL);
                    delete ft;
                }

                //printf("%d: %d %d %d\n",tmp.id, tmp.type, tmp.cost, tmp.sort);

                cards->cards_holder.push_back(tmp);
            }

            period = 0;
            oldoff = off + 1;
        }
        else
            if (txt[off] == ',')
                period++;

    }

    for (uint32_t i=0; i < cards->cards_holder.size(); i++)
        cards->card_mapping[cards->cards_holder[i].id] = &cards->cards_holder[i];

    free(txt);
    return true;
}


s_card *cards_get_card(s_cards *cards, uint32_t id)
{
    card_map_it it = cards->card_mapping.find(id);
    if (it == cards->card_mapping.end())
    {
        it = cards_common->card_mapping.find(id);
        if (it == cards_common->card_mapping.end())
            return NULL;
    }
    return it->second;
}


void cards_draw_card(s_card * card, int16_t x, int16_t y, float scale, uint8_t plane)
{
    gr_sprite spr(*card->tex);
    gr_setxy_sprite(&spr,x,y);
    gr_setscale_sprite(&spr,scale,scale);
    gr_draw_sprite(&spr);
}

