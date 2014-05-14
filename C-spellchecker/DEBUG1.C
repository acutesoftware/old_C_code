void BuildTree(void)    /* build nodes from GetNode into a BTree*/
{
        char report[256];               /* text on report at end of check */

        Node_type *bp;  /* pointer to current node      */
        int count = 0;  /* number of nodes so far       */
        int level;      /* level of current node        */
        int x = 0;      /* DEBUG */
        Node_type *lastnode[13];        /*pointers to last node on each level */
        FILE *fp;       /* file pointer of the words */
        logfile = fopen("C:\debug.as3", "a");   /* open the DEBUG file */
        fprintf(logfile, "\n\nStarted Buildtree--------------\n\n");

        for( level = 0; level < MAXHEIGHT; level++)
                lastnode[level] = NULL;   /* clear lastnodes to NULL */


        if (( fp = fopen("TEST.DAT", "rt")) != NULL) {  /* open the word file */
          while(!feof(fp))       {      /* if file has not finished (ie not NULL) */
            /*  while((p = GetNode(fp)) != NULL)        /* get new node from disk */
                p = GetNode(fp);                /* get new node from disk */
/*  fprintf(logfile, "After GetNode %d- p->left = %p, p->right = %p, p->info.word = %s\n", count, bp->left, bp->right, bp->info.word);*/
                Insert(p, ++count, lastnode);   /* insert node into Btree */
  fprintf(logfile, "%d. (%p) left= %p, right= %p, word = %p %s\n", count, p, p->left, p->right, p->info, p->info.word);
  printf("%d. (%p) left= %p, right= %p, word = %p %s\n", count, p, p->left, p->right, p->info, p->info.word);

   /*-------------------------------DEBUG------------------------ */
/*   sprintf(report, "p->left = %s\n, p->right = %s\n, p->info.word = %s\n", p->left, p->right, p->info.word);*/
/*   sprintf(report, "Building Node %d-------------\np->left = %p _%s_\n, p->right = %p _%s_\n, p->info.word = %p _%s_\n\n", count, p->left, p->left, p->right, p->right, p->info.word, p->info.word);*/
 /*  sprintf(report, "p->left = %p, p->right = %p, p->info.word = %p\n", bp->left, bp->right, bp->info.word);
/*   ErrorMessage(report);  /* causes lockups when adding 'fp' */
/*     fprintf(logfile, "p->left = %p, p->right = %p, p->info.word = %p _%s_\n", p->left, p->right, p->info.word, p->info.word);
   /*------------------------------------------------------------ */

          }
/*        fclose(logfile);*/
          fclose(fp);   /* close the file with words in it */
        }

        p = FindRoot(lastnode);
        ConnectSubtrees(lastnode);

 sprintf(report, "ROOT of Btree\np->left = %p, p->right = %p, p->info.word = %p _%s_\n", p->left, p->right, p->info.word, p->info.word);
 fprintf(logfile, report);
 printf(report);

        /* root = FindRoot(lastnode);*/


   /*-------------------------------DEBUG------------------------ */

/*   bp = FindRoot(lastnode); this doesnt lockup the function when exiting */
   x = 1;
   printf("\n\n\tThe Binary Tree has been built with %d words\n\n", count);
   printf("%d. (%p) L=%p R= %p, word = %p %s\n", count, p, p->left, p->right, p->info.word);
   printf(" (%p) p->info.word =  %s\n", p->info.word, p->info.word);
   printf("'p' formatted 'p' p= %p\n *p=%p\n &p=%p\n", p, p->info.word, &p);
   printf("'p' formatted 's' p= %s\n *p=%s\n &p=%s\n", p, p->info.word, &p);
   fprintf(logfile, "'p' formatted 'p' p= %p\n *p=%p\n &p=%p\n", p, *p, &p);
   fprintf(logfile, "'p' formatted 's' p= %s\n *p=%s\n &p=%s\n", p, *p, &p);

   while(x != 0) {
           x = LeftRight();
           if (x == 1)
                if(p->left)
                        p = p->left;
                else
                        printf("Cant move Left into NULL\n");
           if (x == 2)
                if(p->right)
                        p = p->right;
                else
                        printf("Cant move Right into NULL\n");
           printf("%d. (%p) left= %p, right= %p, word = %p\n", count, p, *p->left, *p->right, *p->info.word);
           printf("'p' formatted 'p' p= %p\n *p=%p\n &p=%p\n", p, *p, &p);
           printf("'p' formatted 's' p= %s\n *p=%s\n &p=%s\n", p, *p, &p);
   printf(" (%p) p->info.word =  %s\n", p->info.word, p->info.word);
           fprintf(logfile, "'p' formatted 'p' p= %p\n *p=%p\n &p=%p\n", p, *p, &p);
           fprintf(logfile, "'p' formatted 's' p= %s\n *p=%s\n &p=%s\n", p, *p, &p);

           fprintf(logfile, "%d. (%p) left= %p, right= %p, word = %p\n", count, p, p->left, p->right, p->info, p->info.word);
/*         fprintf(logfile, " (%p) word =  %s\n", p, p->info.word);*/
           fprintf(logfile, "L= %s\nR=%s\n W=%s\n", *p->left, *p->right, *p->info.word);

   }
   printf("Finished DEBUG");


 fclose(logfile);


   /*------------------------------------------------------------ */

/*      Inorder(root);*/
        ErrorMessage("Finished Building Tree... About to exit function (BANG!)");
      /*        Inorder(p);     /* visit each node in order */
        ;
     /* return root;                    /* return the root of the Btree */
     /* return;         /* return shit because it locks up & *root = GLOBAL*/

}

