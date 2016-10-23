#include "rahmen.h"

rahmen::rahmen(const char* eingabedatei)
{
    FILE * fp=fopen(eingabedatei,"r+");
    if(fp==NULL)
    {
        std::cout<<"Eingabedatei lässt sich nicht öffnen."<<std::endl;

    }
    fseek(fp,0,SEEK_END);
    dateigroese=ftell(fp);
    fseek(fp,0,SEEK_SET);
    datei=new char[dateigroese];
    if(fread(datei,1,dateigroese,fp)!=dateigroese)
    {
        std::cout<<"Eingabedatei lässt sich nicht lesen."<<std::endl;
    }
    fclose(fp);

    std::string buffer;
    unsigned int i=0;
    for(i;i<dateigroese;i++)
    {
        if(datei[i]=='\n')
            break;
        buffer+=datei[i];
    }
    seitenlaenge=std::stoi(buffer);

    char ** feld;
    this->allocate_feld(feld);
    this->allocate_feld(buffer_feld);

    i++;
    for(unsigned int y=0;y<seitenlaenge;y++)
    {
        for(unsigned int x=0;x<seitenlaenge;x++)
        {
            if(datei[i+x+y*seitenlaenge]=='\n')    i++;
            feld[x][y]=datei[i+x+y*seitenlaenge];
        }
    }

    this->loese(feld);

}

void rahmen::allocate_feld(char **&f)
{
    f = new char*[seitenlaenge];
    for(unsigned int i = 0; i <= seitenlaenge; ++i)
        f[i] = new char[seitenlaenge];
}

void rahmen::kopiere_feld(char **&quelle, char **&ziel)
{
    for(unsigned int y=0;y<seitenlaenge;y++)
    {
        for(unsigned int x=0;x<seitenlaenge;x++)
        {
            ziel[x][y]=quelle[x][y];
        }
    }
}

bool rahmen::vergleiche(char **f1, char **f2)
{
    bool t_bool=true;
    for(unsigned int y=seitenlaenge-2;y>=1;y--)
    {
        for(unsigned int x=seitenlaenge-2;x>=1;x--)
        {
            if(f1[x][y]!=f2[x][y])
            {
                return false;
            }

        }
    }
    return true;
}

void rahmen::zeige_feld(char **f)
{
    std::cout<<std::endl;

    for(unsigned int y=0;y<seitenlaenge;y++)
    {
        for(unsigned int x=0;x<seitenlaenge;x++)
        {
            std::cout<<f[x][y];
        }
        std::cout<<std::endl;
    }

    std::cout<<std::endl;
}


void rahmen::rotieren_links(char **&f)
{
    for(unsigned int y=0;y<seitenlaenge;y++)
    {
        for(unsigned int x=0;x<seitenlaenge;x++)
        {
            buffer_feld[x][y]=f[seitenlaenge-y-1][x];
        }
    }
    this->kopiere_feld(buffer_feld,f);
    this->gravitation(f);
}

void rahmen::rotieren_rechts(char **&f)
{
    for(unsigned int y=0;y<seitenlaenge;y++)
    {
        for(unsigned int x=0;x<seitenlaenge;x++)
        {
            buffer_feld[x][y]=f[y][seitenlaenge-x-1];
        }
    }
    this->kopiere_feld(buffer_feld,f);
    this->gravitation(f);
}

void rahmen::gravitation(char **&f)
{
    short richtung[2];
    unsigned short laenge;
    unsigned short verschiebung;
    char zeichen;
    bool t_bool;
    bool benutzt[10];
    for(int i=0;i<10;i++)
    {
        benutzt[i]=false;
    }

    for(unsigned int y=seitenlaenge-2;y>=1;y--)
    {
        for(unsigned int x=seitenlaenge-2;x>=1;x--)
        {
            if(f[x][y]!='#' && f[x][y]!=' ' && benutzt[f[x][y]-'0']!=true)
            {
                zeichen=f[x][y];
                benutzt[zeichen-'0']=true;

                if(f[x-1][y]==zeichen)
                {
                    richtung[0]=1;
                    richtung[1]=0;
                }
                if(f[x][y-1]==zeichen)
                {
                    richtung[0]=0;
                    richtung[1]=1;
                }

                for(int i=1;true;i++)
                {
                    if(x-richtung[0]*i<seitenlaenge && y-richtung[1]*i<seitenlaenge)
                    {
                        if(f[x-richtung[0]*i][y-richtung[1]*i]==zeichen)
                        {
                            laenge=i+1;
                        }
                        else
                        {
                            break;
                        }
                    }
                    else
                    {
                        break;
                    }
                }

                if(richtung[0]==0 && f[x][y]!=f[x][y+1])
                {
                    for(verschiebung=1;true;verschiebung++)
                    {
                        if(f[x][y+verschiebung]!=' ')
                        {
                            verschiebung--;
                            break;
                        }
                    }

                    if(verschiebung>0)
                    {

                        for(int i=0;i<verschiebung;i++)
                        {
                            f[x][y+i-laenge+1]=' ';
                            f[x][y+i+1]=zeichen;
                        }


                        for(int i=0;i<10;i++)
                        {
                            benutzt[i]=false;
                        }
                    }
                }
                if(richtung[1]==0 && f[x][y]!=f[x+1][y])
                {
                    for(verschiebung=1;true;verschiebung++)
                    {
                        t_bool=true;

                        for(int i=0;i<laenge;i++)
                        {

                           if(f[x-i][y+verschiebung]!=' ')
                           {
                               t_bool=false;
                               break;
                           }
                        }

                        if(t_bool==false)
                        {
                            verschiebung--;
                            break;
                        }
                    }

                    if(verschiebung>0)
                    {
                        for(int i=0;i<laenge;i++)
                        {
                            f[x-i][y]=' ';
                            f[x-i][y+verschiebung]=zeichen;
                        }

                        for(int i=0;i<10;i++)
                        {
                            benutzt[i]=false;
                        }
                    }
                }

            }
        }
    }

}

int rahmen::ist_loesung(char **f)
{
    unsigned int x,y;
    y=0;
    for(x=0;x<seitenlaenge;x++)
    {
        if(f[x][y]!='#' && f[x][y]!=' ')
        {
            return true;
        }
    }
    y=seitenlaenge-1;
    for(x=0;x<seitenlaenge;x++)
    {
        if(f[x][y]!='#' && f[x][y]!=' ')
        {
            return true;
        }
    }
    x=0;
    for(y=0;y<seitenlaenge;y++)
    {
        if(f[x][y]!='#' && f[x][y]!=' ')
        {
            return true;
        }
    }
    x=seitenlaenge-1;
    for(y=0;y<seitenlaenge;y++)
    {
        if(f[x][y]!='#' && f[x][y]!=' ')
        {
            return true;
        }
    }
    return false;
}


void rahmen::loese(char **f)
{
    std::vector<std::vector<char **> > baum;
    std::vector<std::vector<std::string>> loes;
    baum.push_back(std::vector<char**>());
    loes.push_back(std::vector<std::string>());
    baum.at(0).push_back(f);
    loes.at(0).push_back("");
    bool t_bool;
    for(unsigned int ebene=0;true;ebene++)
    {
        baum.push_back(std::vector<char**>());
        loes.push_back(std::vector<std::string>());

        if(baum.at(ebene).size()==0)
        {
            std::cout<<"Ebene : "<<ebene<<"  Groese : "<<baum.at(ebene).size()<<" Zuwachsrate : "<<((double)baum.at(ebene).size())/((double)baum.at(ebene-1).size()*2)<<std::endl;
            std::cout<<"Keine Loesung vorhanden."<<std::endl;
            return;
        }
        for(unsigned int k=0;k<baum.at(ebene).size();k++)
        {
            this->allocate_feld(f);
            this->kopiere_feld(baum.at(ebene).at(k),f);
            this->rotieren_links(f);
            if(this->ist_loesung(f))
            {
                this->zeige_loesung(baum.at(0).at(0),loes.at(ebene).at(k)+"l");
                return;
            }


            t_bool=false;
            for(unsigned int i=0;i<baum.size();i++)
            {
                for(unsigned int i2=0;i2<baum.at(i).size();i2++)
                {
                    t_bool=this->vergleiche(f,baum.at(i).at(i2));
                    if(t_bool) break;
                }
                if(t_bool) break;
            }
            if(!t_bool)
            {
                baum.at(ebene+1).push_back(f);
                loes.at(ebene+1).push_back(loes.at(ebene).at(k)+"l");
            }


            this->allocate_feld(f);
            this->kopiere_feld(baum.at(ebene).at(k),f);
            this->rotieren_rechts(f);
            if(this->ist_loesung(f))
            {
                this->zeige_loesung(baum.at(0).at(0),loes.at(ebene).at(k)+"r");
                return;
            }

            t_bool=false;
            for(unsigned int i=0;i<baum.size();i++)
            {
                for(unsigned int i2=0;i2<baum.at(i).size();i2++)
                {
                    t_bool=this->vergleiche(f,baum.at(i).at(i2));
                    if(t_bool) break;
                }
                if(t_bool) break;
            }
            if(!t_bool)
            {
                baum.at(ebene+1).push_back(f);
                loes.at(ebene+1).push_back(loes.at(ebene).at(k)+"r");
            }


        }
        if(ebene!=0)
        std::cout<<"Ebene : "<<ebene<<"  Groese : "<<baum.at(ebene).size()<<" Zuwachsrate : "<<((double)baum.at(ebene).size())/((double)baum.at(ebene-1).size()*2)<<std::endl;
    }

}

void rahmen::zeige_loesung(char **f,std::string l)
{
    std::cout<<"Beste Loesung mit Laenge "<<l.length()<<" : "<<l<<std::endl;
    for(unsigned int i=0;i<l.length();i++)
    {
        if(l[i]=='r')
        {
            this->rotieren_rechts(f);
        }
        else
        {
            this->rotieren_links(f);
        }
        this->zeige_feld(f);

    }
    return;
}

