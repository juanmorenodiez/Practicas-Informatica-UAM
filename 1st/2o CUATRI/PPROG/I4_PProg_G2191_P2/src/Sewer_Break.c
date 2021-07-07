#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"


int main(){

  int i;
  char option;
  
  system("clear");
  fprintf(stdout, "\n");


  fprintf(stdout, "                              %s██████ ▓█████  █     █░▓█████  ██▀███      ▄▄▄▄    ██▀███  ▓█████ ▄▄▄       ██ ▄█▀\n",KGRN);
  fprintf(stdout, "                              %s▒██    ▒ ▓█   ▀ ▓█░ █ ░█░▓█   ▀ ▓██ ▒ ██▒   ▓█████▄ ▓██ ▒ ██▒▓█   ▀▒████▄     ██▄█▒ \n",KGRN);
  fprintf(stdout, "                              %s░ ▓██▄   ▒███   ▒█░ █ ░█ ▒███   ▓██ ░▄█ ▒   ▒██▒ ▄██▓██ ░▄█ ▒▒███  ▒██  ▀█▄  ▓███▄░ \n",KGRN);
  fprintf(stdout, "                              %s  ▒   ██▒▒▓█  ▄ ░█░ █ ░█ ▒▓█  ▄ ▒██▀▀█▄     ▒██░█▀  ▒██▀▀█▄  ▒▓█  ▄░██▄▄▄▄██ ▓██ █▄\n",KGRN); 
  fprintf(stdout, "                              %s▒██████▒▒░▒████▒░░██▒██▓ ░▒████▒░██▓ ▒██▒   ░▓█  ▀█▓░██▓ ▒██▒░▒████▒▓█   ▓██▒▒██▒ █▄\n",KGRN);
  fprintf(stdout, "                              %s▒ ▒▓▒ ▒ ░░░ ▒░ ░░ ▓░▒ ▒  ░░ ▒░ ░░ ▒▓ ░▒▓░   ░▒▓███▀▒░ ▒▓ ░▒▓░░░ ▒░ ░▒▒   ▓▒█░▒ ▒▒ ▓▒\n",KGRN);
  fprintf(stdout, "                              %s░ ░▒  ░ ░ ░ ░  ░  ▒ ░ ░   ░ ░  ░  ░▒ ░ ▒░   ▒░▒   ░   ░▒ ░ ▒░ ░ ░  ░ ▒   ▒▒ ░░ ░▒ ▒░\n",KGRN);
  fprintf(stdout, "                              %s░  ░  ░     ░     ░   ░     ░     ░░   ░     ░    ░   ░░   ░    ░    ░   ▒   ░ ░░ ░ \n",KGRN);
  fprintf(stdout, "                              %s      ░     ░  ░    ░       ░  ░   ░         ░         ░        ░  ░     ░  ░░  ░   \n",KGRN);
  
  fprintf(stdout,"%s          _-~~~-_       _-~~~-_ \n", KCYN);
  fprintf(stdout,"%s        /~       ~\\    :    ,  \\ \n", KCYN);
  fprintf(stdout,"%s       '           ~   ,   |:  : \n", KCYN);
  fprintf(stdout,"%s      {      /~~\\  :--~""""\\.:  :    %s  ___  _  _   __    __   ____  ____     __   __ _     __  ____  ____  __  __   __ _ \n", KCYN, KYEL);
  fprintf(stdout,"%s       \\    (... :   /^\\  /^\\ ;  %s / __)/ )( \\ /  \\  /  \\ / ___)(  __)   / _\\ (  ( \\   /  \\(  _ \\(_  _)(  )/  \\ (  ( \\ \n", KCYN, KYEL);
  fprintf(stdout,"%s        ~\\_____     |   | | |:~  %s( (__ ) __ ((  O )(  O )\\___ \\ ) _)   /    \\/    /  (  O )) __/  )(   )((  O )/    /\n", KCYN, KYEL);
  fprintf(stdout,"%s              /     |__O|_|O|;   %s \\___)\\_)(_/ \\__/  \\__/ (____/(____)  \\_/\\_/\\_)__)   \\__/(__)   (__) (__)\\__/ \\_)__)\n", KCYN, KYEL);
  fprintf(stdout,"%s             (     /       O \\ \n", KCYN);
  fprintf(stdout,"%s              \\   ( `\\_______/) \n", KCYN);
  fprintf(stdout,"%s               `\\  \\         / \n", KCYN);
  fprintf(stdout,"%s                 )  ~-------~'\\ \n", KCYN);
  fprintf(stdout,"%s                /              \\ \n", KCYN);
  fprintf(stdout,"%s               :               ||      %s· S to start a new game                  %sad8888888888ba\n", KCYN, KYEL, KBLU);
  fprintf(stdout,"%s               |  |            ||                                              %sdP'         `~8b,\n", KCYN, KBLU);
  fprintf(stdout,"%s               |  |.======[]==+'|      %s· E to exit                             %s8  ,aaa,       ""Y888a     ,aaaa,     ,aaa,  ,aa,\n", KCYN, KYEL, KBLU);
  fprintf(stdout,"%s              (~~~~)       |   |~)                                             %s8  8' `8           ""8baaaad~~~~baaaad~~~~baad~~8b\n", KCYN, KBLU);
  fprintf(stdout,"%s              /    \\       |   | \\     %s                                        %s8  8   8              ~~~~      ~~~~      ~~    8b\n", KCYN, KYEL, KBLU);
  fprintf(stdout,"%s  ~\\\\          \\___/)______/^\\__|_/                                            %s8  8, ,8         ,aaaaaaaaaaaaaaaaaaaaaaaaddddd88P\n", KCYN, KBLU);
  fprintf(stdout,"%s    `\\\\      //    |  |      | |       %s                                        %s8  `~~~'       ,d8~~\n", KCYN, KYEL, KBLU);
  fprintf(stdout,"%s      `\\\\__//'     |  |      | |                                               %sYb,         ,ad8"" \n", KCYN, KBLU);
  fprintf(stdout,"%s         ~~       (~~~~)    (~~~)                                              %s~Y8888888888P~\n", KCYN, KBLU);
  fprintf(stdout,"%s                 /     =\\..'    =_ \n", KCYN);
  fprintf(stdout,"%s                |__________)________)- \n", KCYN);

  for(i=0;i<3;i++)
    fprintf(stdout, "\n");
  
  scanf("%c", &option);
  
  if(option == 'E' ) return 2;
  if(option == 'S') system("./goose data.dat");
  
  return 0;                                                 
}




