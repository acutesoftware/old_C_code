   /*-------------------------------DEBUG------------------------ */

/*   bp = FindRoot(lastnode); this doesnt lockup the function when exiting */
   x = 1;
/*   printf("\n\n\tThe Binary Tree has been built with %d words\n\n", count);
   sprintf("L=%p R=%p, word=%p _%s_\n", p->left, p->right, p->info.word, p->info.word);
   printf(report);
   fprintf(logfile, report);*/
   x = 0;       /* remove this line when debugging */

   while(x != 0) {
           x = LeftRight();
           if (x == 1)
                if(p->left) {
                        p = p->left;
                        fprintf(logfile, "Moving to Left\n");
                        }
                else
                        printf("Cant move Left into NULL\n");
           if (x == 2)
                if(p->right) {
                        p = p->right;
                        fprintf(logfile, "Moving to Right\n");
                        }
                else
                        printf("Cant move Right into NULL\n");

    sprintf(report, "L=%p R=%p, word=%p _%s_\n", p->left, p->right, &p->info.word, p);
    printf(report);
    fprintf(logfile, report);


   }
  /* printf("Finished DEBUG");*/

