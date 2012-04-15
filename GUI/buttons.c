#include <gtk/gtk.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "governor.h"
#include "fileop.h"

GtkWidget *radiobutton1, *radiobutton2,*radiobutton3,*radiobutton4,*radiobutton5,*radiobutton6;
GtkWidget *hseparator,*label1,*label2,*label3;
int flag;

void *readAndDisplay()
{
	FILE *fp;
	char c1[40];
 	char error1[]="File Not Found";
 	char error2[]="Restart or Wait";
	int turn=1;
	while(flag)
	{
		if((fp=fopen("display.txt","r"))!=NULL)
			{
				while(fgets(c1,sizeof(c1),fp)!=NULL)
				{
					if(turn==1)
						{	
							gtk_label_set_text (label1,c1);	
							//turn=2;		
						}	
					else if(turn==2)
						{
							gtk_label_set_text (label2,c1);	
							//turn=3;		
						}
					else if(turn==3)
						{
							gtk_label_set_text (label3,c1);	
							//turn=3;		
						}
					turn++;
					if(turn==4){turn=1;}	


				}
					fclose(fp);
					sleep(1);
			}
		else
			{	
				gtk_label_set_text (label1,error1);
				gtk_label_set_text (label2,error2);
				gtk_label_set_text (label3,"");
				sleep(1);	
			}

	}
}

void closeApp ( GtkWidget *window, gpointer data)
{
  gtk_main_quit();
}

void add_widget_with_label ( GtkContainer * box, gchar * caption, GtkWidget * widget)
{
  GtkWidget *label = gtk_label_new (caption);
//gtk_label_set_justify(label,GTK_JUSTIFY_RIGHT);  
//gtk_misc_set_alignment (widget,1,0.5);
gtk_misc_set_alignment (label,1,0.5);
//gtk_alignment_set_padding (widget,0,4,0,0);
 GtkWidget *hbox = gtk_hbox_new (TRUE, 1);
  gtk_container_add(GTK_CONTAINER (hbox), label);
gtk_container_add(GTK_CONTAINER (hbox), widget);

  
 
  gtk_container_add(box, hbox);
}

void add_widget_without_label ( GtkContainer * box, GtkWidget * widget)
{

gtk_misc_set_alignment (widget,0.5,0.5);
GtkWidget *hbox = gtk_hbox_new (TRUE,1);
gtk_container_add(GTK_CONTAINER (hbox), widget);
gtk_container_add(box, hbox);

}


void radio_button_clicked1(GtkWidget *button, gpointer data)
{
  gboolean active = gtk_toggle_button_get_active(radiobutton1);
	if(active)
	{
	 // printf("Button1 %i \t",active);
	 // onDemand();
		setAuto();
	}
}

void radio_button_clicked2(GtkWidget *button, gpointer data)
{
  gboolean active = gtk_toggle_button_get_active(radiobutton2);
	if(active)
	{
	  //printf("Button2 %i \t",active);
	  //setFreq(100);
	  set100();
	}
}

void radio_button_clicked3(GtkWidget *button, gpointer data)
{
  gboolean active = gtk_toggle_button_get_active(radiobutton3);
	if(active)
	{
	  //printf("Button3 %i \t",active);
	  //setFreq(75);
set75();
	}
}

void radio_button_clicked4(GtkWidget *button, gpointer data)
{
  gboolean active = gtk_toggle_button_get_active(radiobutton4);
	if(active)
	{
	  //printf("Button4 %i \t",active);
	  //setFreq(50);
 set50();
	}
}

void radio_button_clicked5(GtkWidget *button, gpointer data)
{
  gboolean active = gtk_toggle_button_get_active(radiobutton5);
	if(active)
	{
	 // printf("Button5 %i \t",active);
//setFreq(33);
set33();
	}
}

/*
void radio_button_clicked6(GtkWidget *button, gpointer data)
{
  gboolean active = gtk_toggle_button_get_active(radiobutton6);
	if(active)
	{
	  printf("Button6 %i \t",active);
	  powerSaver();
	}
}
*/

gint main (gint argc, gchar *argv[])
{
  GtkWidget *window;
  GtkWidget *button;       
  GtkWidget *vbox;
  pthread_t thread1;
	int iret;


  gtk_init (&argc, &argv);
setAuto();
  //window = gtk_window_new(GTK_WINDOW_POPUP);
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(window),200,200);
 gtk_window_set_resizable(GTK_WINDOW(window),TRUE);  
gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_NONE);
gtk_window_set_title(GTK_WINDOW(window),"GPU FS");  
  g_signal_connect ( G_OBJECT (window), "destroy",
                       G_CALLBACK (closeApp), NULL);



  radiobutton1 = gtk_radio_button_new(NULL);
  radiobutton2 = gtk_radio_button_new_from_widget(GTK_RADIO_BUTTON(radiobutton1));
  radiobutton3 = gtk_radio_button_new_from_widget(GTK_RADIO_BUTTON(radiobutton1));
  radiobutton4 = gtk_radio_button_new_from_widget(GTK_RADIO_BUTTON(radiobutton1));
  radiobutton5 = gtk_radio_button_new_from_widget(GTK_RADIO_BUTTON(radiobutton1));
  //radiobutton6 = gtk_radio_button_new_from_widget(GTK_RADIO_BUTTON(radiobutton1));
 hseparator=gtk_hseparator_new ();
label1 =gtk_label_new(NULL);
label2 =gtk_label_new(NULL); 
label3 =gtk_label_new(NULL);

  vbox = gtk_vbox_new (TRUE, 4); 
  add_widget_with_label (GTK_CONTAINER(vbox), "Auto:", radiobutton1);
  add_widget_with_label (GTK_CONTAINER(vbox), NULL, hseparator);
  add_widget_with_label (GTK_CONTAINER(vbox), "100%:",radiobutton2);
  add_widget_with_label (GTK_CONTAINER(vbox), "75%:", radiobutton3);
  add_widget_with_label (GTK_CONTAINER(vbox), "50%:", radiobutton4);
  add_widget_with_label (GTK_CONTAINER(vbox), "33%:", radiobutton5);//
  add_widget_without_label (GTK_CONTAINER(vbox),label1);
  add_widget_without_label (GTK_CONTAINER(vbox),label2);
  add_widget_without_label (GTK_CONTAINER(vbox),label3);

  //add_widget_with_label (GTK_CONTAINER(vbox), "PowerSaver:", radiobutton6);
 
  g_signal_connect(G_OBJECT(radiobutton1), "toggled", 
                     G_CALLBACK(radio_button_clicked1), NULL);
  g_signal_connect(G_OBJECT(radiobutton2), "toggled", 
                     G_CALLBACK(radio_button_clicked2), NULL);
  g_signal_connect(G_OBJECT(radiobutton3), "toggled", 
                     G_CALLBACK(radio_button_clicked3), NULL);
  g_signal_connect(G_OBJECT(radiobutton4), "toggled", 
                     G_CALLBACK(radio_button_clicked4), NULL);
  g_signal_connect(G_OBJECT(radiobutton5), "toggled", 
                     G_CALLBACK(radio_button_clicked5), NULL);
  //g_signal_connect(G_OBJECT(radiobutton6), "toggled", 
   //                  G_CALLBACK(radio_button_clicked6), NULL);

	
  gtk_container_add(GTK_CONTAINER(window), vbox);		
  gtk_widget_show_all(window);
flag=1;
iret = pthread_create( &thread1, NULL, readAndDisplay, NULL);
  gtk_main ();
  flag = 0;
 pthread_join( thread1, NULL);	
system("killall master");	
  return 0;
}


