/*****************************************************************************
 * Copyright (C) Vaishnavi R.B. vaishnavibobde09@gmail.com
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/

#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <string.h>
#include "project.h"

GtkWidget *window;
GtkWidget *layout;
int token = -1;
int count = -1;
int new = 0;
int store[512];
char *gates[16] = {"AND", "OR", "NOR", "NOT", "XOR", "NAND", "INPUT_ON", "INPUT_OFF", "OUTPUT", "HORI_WIRE", "VERT_WIRE"};
gboolean drag = FALSE;

int AND_output(int input_1, int input_2) {
	if(input_1 == 1 && input_2 == 1)
		return 1;
	else
		return 0;
}

int OR_output(int input_1, int input_2) {
	if(input_1 == 0 && input_2 == 0)
		return 0;
	else
		return 1;
}

int NOT_output(int input_1) {
	if(input_1 == 1)
		return 0;
	else
		return 1;
}

int NAND_output(int input_1, int input_2) {
	if(input_1 == 1 && input_2 == 1)
		return 0;
	else
		return 1;
}

int NOR_output(int input_1, int input_2) {
	if(input_1 == 0 && input_2 == 0)
		return 1;
	else
		return 0;
}

int XOR_output(int input_1, int input_2) {
	if(input_1 == input_2)
		return 0;
	else
		return 1;
}

int search(char *key) {
	int i = 0;
	for (i = 0; i < token; i++) {
		if(*(array[i].gate) == *key)
			return i;
	}
}

int CALCULATE() {
	int i = 0, in1 = 0, in2 = 0, temp = 0, j = 0, k = 0, flag = 0;
	int tmp_store[count + 1];
	for(k = 0; k <= count; k++) {
		tmp_store[k] = store[k];
		if(tmp_store[k] == 60)
			flag = 1;
	}
	if(count == 1 && tmp_store[0] == 60 && tmp_store[1] == 0)
		return 1;
	if(count == 1 && tmp_store[0] == 60 && tmp_store[1] == 1)
		return 0;
	j = count;
	i = count;
	if(flag == 1) {
		while(j >= 1) {
			if(tmp_store[j] == 1)
				in1 = 1;
			if(tmp_store[j] == 0)
				in1 = 0;
			if(tmp_store[j-1] == 1)
				in2 = 1;
			if(tmp_store[j-1] == 0)
				in2 = 0;
			while(i >= 0) {
				if(tmp_store[i] >= 10 && tmp_store[i] <= 60) {

					if(tmp_store[i] == 10) {
						temp = AND_output(in1, in2);
					}
					else if(tmp_store[i] == 20) {
						temp = OR_output(in1, in2);
					}
					else if(tmp_store[i] == 30) {
						temp = NOR_output(in1, in2);
					}
					else if(tmp_store[i] == 40) {
						temp = XOR_output(in1, in2);
					}
					else if(tmp_store[i] == 50) {
						temp = NAND_output(in1, in2);
					}
					else if(tmp_store[i] == 60) {
						temp = NOT_output(in1);
						j = j + 1;
					}
					i--;
					break;
				}
				else {
					i--;
					continue;
				}
			}
			tmp_store[i + 1] = temp;
			j = j - 2;
		}
	}
	else {
		while(j > 1) {
			if(tmp_store[j] == 1)
				in1 = 1;
			if(tmp_store[j] == 0)
				in1 = 0;
			if(tmp_store[j-1] == 1)
				in2 = 1;
			if(tmp_store[j-1] == 0)
				in2 = 0;
			while(i >= 0) {
				if(tmp_store[i] >= 10 && tmp_store[i] <= 60) {

					if(tmp_store[i] == 10) {
						temp = AND_output(in1, in2);
					}
					else if(tmp_store[i] == 20) {
						temp = OR_output(in1, in2);
					}
					else if(tmp_store[i] == 30) {
						temp = NOR_output(in1, in2);
					}
					else if(tmp_store[i] == 40) {
						temp = XOR_output(in1, in2);
					}
					else if(tmp_store[i] == 50) {
						temp = NAND_output(in1, in2);
					}
					else if(tmp_store[i] == 60) {
						temp = NOT_output(in1);
						j = j + 1;
					}
					i--;
					break;
				}
				else {
					i--;
					continue;
				}
			}
			tmp_store[i + 1] = temp;
			j = j - 2;
		}
	}
	return temp;
}

void save_to_file(char *filename) {
	FILE *fp;
	GtkWidget *image;
	image = gtk_image_new_from_file("AND.png");
	fp = fopen(filename, "w");
	fwrite(image, 1, 1, fp);
	fclose(fp);
}

static gboolean handleMove( GtkWidget *widget, GdkEventButton *event, gpointer data ){
	struct Icon *icon = (struct Icon*) data;
  	icon->x = (int)event->x;
  	icon->y = (int)event->y;
  	gtk_layout_move (GTK_LAYOUT (layout), widget, icon->x, icon->y);
  	//printf("move (%d , %d) %d\n", icon->x, icon->y,event->time);
  	return TRUE;
}

static gboolean handleRelease( GtkWidget *widget, GdkEventButton *event, gpointer data ){
  	
  	g_signal_handlers_disconnect_by_func(widget, handleMove, data);
  	//printf("%s\n", "disconnect_handleMove");
  	struct Icon *icon = (struct Icon*) data;
  	//printf("position (%d , %d)\n", icon->x, icon->y);
  	
  	array[token].x = icon->x;
  	array[token].y = icon->y;
 
  	drag = FALSE;
  	return TRUE;
}

static gboolean handleClick( GtkWidget *widget, GdkEventButton *event, gpointer data ){
  	//struct Icon *icon = (struct Icon*) data;

  	if(!drag){
    		drag = TRUE;
    		//printf("%s\n", "connect_handleMove");
    		g_signal_connect (G_OBJECT (widget), "motion_notify_event" ,G_CALLBACK(handleMove), data);
    		g_signal_connect (G_OBJECT (widget), "button-release-event",G_CALLBACK(handleRelease), data);
    		//printf("position (%d , %d)\n", icon->x, icon->y);
    		return TRUE;
  	}else
     		return TRUE;

}

void AND_clicked(GtkWidget *button, gpointer data) {
	GtkWidget *image, *event;
	gint i = 0;
	event = gtk_event_box_new ();
	image = gtk_image_new_from_file("AND.png");
	
  	icons[i].image = image;
    	icons[i].x = i*50;
    	icons[i].y = i*50;
    	icons[i].width = 50;
    	icons[i].height = 50;
    	gtk_container_add (GTK_CONTAINER (event), image);
    	gtk_layout_put (GTK_LAYOUT (layout), event, i*50, i*50);
    	gtk_event_box_set_above_child(GTK_EVENT_BOX(event), FALSE);
    	token++;
        g_signal_connect (G_OBJECT (event), "button_press_event", G_CALLBACK (handleClick), (gpointer) &icons[i]);
        count++;
        store[count] = 10;
        
        array[token].gate = gates[0];
        
    	gtk_event_box_set_visible_window(GTK_EVENT_BOX(event),(gboolean)FALSE);
    	gtk_widget_show (image);
    	gtk_widget_show (event);
}

void OR_clicked(GtkWidget *button, gpointer data) {
	GtkWidget *image, *event;
	gint i = 0;
	event = gtk_event_box_new ();
	image = gtk_image_new_from_file("OR.png");
	
    	icons[i].image = image;
    	icons[i].x = i*50;
    	icons[i].y = i*50;
    	icons[i].width = 50;
	icons[i].height = 50;
    	gtk_container_add (GTK_CONTAINER (event), image);
    	gtk_layout_put (GTK_LAYOUT (layout), event, i*50, i*50);
    	gtk_event_box_set_above_child(GTK_EVENT_BOX(event), FALSE);
    	token++;
    	g_signal_connect (G_OBJECT (event), "button_press_event", G_CALLBACK (handleClick), (gpointer) &icons[i]);
    	count++;
    	store[count] = 20;
    	
    	array[token].gate = gates[1];
        
    	gtk_event_box_set_visible_window(GTK_EVENT_BOX(event),(gboolean)FALSE);
    	gtk_widget_show (image);
    	gtk_widget_show (event);
}

void NOR_clicked(GtkWidget *button, gpointer data) {
	GtkWidget *image, *event;
	gint i = 0;
	event = gtk_event_box_new ();
	image = gtk_image_new_from_file("NOR.png");
	
    	icons[i].image = image;
    	icons[i].x = i*50;
    	icons[i].y = i*50;
    	icons[i].width = 50;
    	icons[i].height = 50;

    	gtk_container_add (GTK_CONTAINER (event), image);
    	gtk_layout_put (GTK_LAYOUT (layout), event, i*50, i*50);
    	gtk_event_box_set_above_child(GTK_EVENT_BOX(event), FALSE);
    	token++;
        g_signal_connect (G_OBJECT (event), "button_press_event", G_CALLBACK (handleClick), (gpointer) &icons[i]);
        count++;
        store[count] = 30;
        
        array[token].gate = gates[2];
        
    	gtk_event_box_set_visible_window(GTK_EVENT_BOX(event),(gboolean)FALSE);
    	gtk_widget_show (image);
    	gtk_widget_show (event);
}

void NOT_clicked(GtkWidget *button, gpointer data) {
	GtkWidget *image, *event;
	gint i = 0;
	event = gtk_event_box_new ();
	image = gtk_image_new_from_file("NOT.png");

	icons[i].image = image;
    	icons[i].x = i*50;
    	icons[i].y = i*50;
    	icons[i].width = 50;
    	icons[i].height = 50;

    	gtk_container_add (GTK_CONTAINER (event), image);
    	gtk_layout_put (GTK_LAYOUT (layout), event, i*50, i*50);
    	gtk_event_box_set_above_child(GTK_EVENT_BOX(event), FALSE);
    	token++;
        g_signal_connect (G_OBJECT (event), "button_press_event", G_CALLBACK (handleClick), (gpointer) &icons[i]);
        count++;
        store[count] = 60;
        
        array[token].gate = gates[3];
        
    	gtk_event_box_set_visible_window(GTK_EVENT_BOX(event),(gboolean)FALSE);
    	gtk_widget_show (image);
    	gtk_widget_show (event);
}

void XOR_clicked(GtkWidget *button, gpointer data) {
	GtkWidget *image, *event;
	gint i = 0;
	event = gtk_event_box_new ();
	image = gtk_image_new_from_file("XOR.png");
	
   	icons[i].image = image;
	icons[i].x = i*50;
	icons[i].y = i*50;
	icons[i].width = 50;
	icons[i].height = 50;

	gtk_container_add (GTK_CONTAINER (event), image);
	gtk_layout_put (GTK_LAYOUT (layout), event, i*50, i*50);
	gtk_event_box_set_above_child(GTK_EVENT_BOX(event), FALSE);
	token++;
	g_signal_connect (G_OBJECT (event), "button_press_event", G_CALLBACK (handleClick), (gpointer) &icons[i]);
	count++;
	store[count] = 40;
	
	array[token].gate = gates[4];
        
	gtk_event_box_set_visible_window(GTK_EVENT_BOX(event),(gboolean)FALSE);
	gtk_widget_show (image);
	gtk_widget_show (event);
}

void NAND_clicked(GtkWidget *button, gpointer data) {
	GtkWidget *image, *event;
	gint i = 0;
	event = gtk_event_box_new ();
	image = gtk_image_new_from_file("NAND.png");
	
    	icons[i].image = image;
    	icons[i].x = i*50;
    	icons[i].y = i*50;
    	icons[i].width = 50;
    	icons[i].height = 50;

    	gtk_container_add (GTK_CONTAINER (event), image);
    	gtk_layout_put (GTK_LAYOUT (layout), event, i*50, i*50);
    	gtk_event_box_set_above_child(GTK_EVENT_BOX(event), FALSE);
    	token++;
        g_signal_connect (G_OBJECT (event), "button_press_event", G_CALLBACK (handleClick), (gpointer) &icons[i]);
        count++;
        store[count] = 50;
        
        array[token].gate = gates[5];
        
    	gtk_event_box_set_visible_window(GTK_EVENT_BOX(event),(gboolean)FALSE);
    	gtk_widget_show (image);
    	gtk_widget_show (event);
}

void INPUT_ON_clicked(GtkWidget *button, gpointer data) {
	GtkWidget *image, *event;
	gint i = 0;
	event = gtk_event_box_new ();
	image = gtk_image_new_from_file("INPUT_ON.png");
	
    	icons[i].image = image;
    	icons[i].x = i*50;
    	icons[i].y = i*50;
    	icons[i].width = 50;
    	icons[i].height = 50;

    	gtk_container_add (GTK_CONTAINER (event), image);
    	gtk_layout_put (GTK_LAYOUT (layout), event, i*50, i*50);
    	gtk_event_box_set_above_child(GTK_EVENT_BOX(event), FALSE);
    	token++;
        g_signal_connect (G_OBJECT (event), "button_press_event", G_CALLBACK (handleClick), (gpointer) &icons[i]);
        count++;
        store[count] = 1;
        
        array[token].gate = gates[6];
        
    	gtk_event_box_set_visible_window(GTK_EVENT_BOX(event),(gboolean)FALSE);
    	gtk_widget_show (image);
    	gtk_widget_show (event);
}

void INPUT_OFF_clicked(GtkWidget *button, gpointer data) {
	GtkWidget *image, *event;
	gint i = 0;
	event = gtk_event_box_new ();
	image = gtk_image_new_from_file("INPUT_OFF.png");
	
    	icons[i].image = image;
    	icons[i].x = i*50;
    	icons[i].y = i*50;
    	icons[i].width = 50;
    	icons[i].height = 50;

    	gtk_container_add (GTK_CONTAINER (event), image);
    	gtk_layout_put (GTK_LAYOUT (layout), event, i*50, i*50);
    	gtk_event_box_set_above_child(GTK_EVENT_BOX(event), FALSE);
    	token++;
        g_signal_connect (G_OBJECT (event), "button_press_event", G_CALLBACK (handleClick), (gpointer) &icons[i]);
        count++;
        store[count] = 0;
        
        array[token].gate = gates[7];
        
    	gtk_event_box_set_visible_window(GTK_EVENT_BOX(event),(gboolean)FALSE);
    	gtk_widget_show (image);
    	gtk_widget_show (event);
}
void OUTPUT_clicked(GtkWidget *button, gpointer data) {
	GtkWidget *image, *event;
	gint i = 0;
	event = gtk_event_box_new ();
	image = gtk_image_new_from_file("OUTPUT_OFF.png");
	
	icons[i].image = image;
	icons[i].x = i*50;
	icons[i].y = i*50;
	icons[i].width = 50;
	icons[i].height = 50;

    	gtk_container_add (GTK_CONTAINER (event), image);
    	gtk_layout_put (GTK_LAYOUT (layout), event, i*50, i*50);
    	gtk_event_box_set_above_child(GTK_EVENT_BOX(event), FALSE);
    	token++;
        g_signal_connect (G_OBJECT (event), "button_press_event", G_CALLBACK (handleClick), (gpointer) &icons[i]);
        
        array[token].gate = gates[8];
        
    	gtk_event_box_set_visible_window(GTK_EVENT_BOX(event),(gboolean)FALSE);
    	gtk_widget_show (image);
    	gtk_widget_show (event);
}

void HORI_WIRE_clicked(GtkWidget *button, gpointer data) {
	GtkWidget *image, *event;
	gint i = 0;
	event = gtk_event_box_new ();
	image = gtk_image_new_from_file("hori.png");

	icons[i].image = image;
	icons[i].x = i*50;
	icons[i].y = i*50;
	icons[i].width = 50;
	icons[i].height = 50;
	
	gtk_container_add (GTK_CONTAINER (event), image);
	gtk_layout_put (GTK_LAYOUT (layout), event, i*50, i*50);
	gtk_event_box_set_above_child(GTK_EVENT_BOX(event), FALSE);
	token++;
	g_signal_connect (G_OBJECT (event), "button_press_event", G_CALLBACK (handleClick), (gpointer) &icons[i]);
	
	array[token].gate = gates[9];
        
	gtk_event_box_set_visible_window(GTK_EVENT_BOX(event),(gboolean)FALSE);
	gtk_widget_show (image);
	gtk_widget_show (event);
}

void VERT_WIRE_clicked(GtkWidget *button, gpointer data) {
	GtkWidget *image, *event;
	gint i = 0;
	event = gtk_event_box_new ();
	image = gtk_image_new_from_file("vert.png");

	icons[i].image = image;
	icons[i].x = i*50;
	icons[i].y = i*50;
	icons[i].width = 50;
	icons[i].height = 50;

	gtk_container_add (GTK_CONTAINER (event), image);
	gtk_layout_put (GTK_LAYOUT (layout), event, i*50, i*50);
	gtk_event_box_set_above_child(GTK_EVENT_BOX(event), FALSE);
	token++;
	g_signal_connect (G_OBJECT (event), "button_press_event", G_CALLBACK (handleClick), (gpointer) &icons[i]);
	
	array[token].gate = gates[10];
        
	gtk_event_box_set_visible_window(GTK_EVENT_BOX(event),(gboolean)FALSE);
	gtk_widget_show (image);
	gtk_widget_show (event);
}

void RUN_clicked(GtkWidget *button, gpointer data) {
	int final = 0, find = 0;
	find = search(gates[8]);
	final = CALCULATE();
	if(final == 1) {
		GtkWidget *image, *event;
		event = gtk_event_box_new ();
		image = gtk_image_new_from_file("OUTPUT_ON.png");
	
		gtk_container_add (GTK_CONTAINER (event), image);
		gtk_layout_put (GTK_LAYOUT (layout), event, array[find].x, array[find].y);
		gtk_event_box_set_above_child(GTK_EVENT_BOX(event), FALSE);
		gtk_event_box_set_visible_window(GTK_EVENT_BOX(event),(gboolean)FALSE);
		gtk_widget_show (image);
		gtk_widget_show (event);
	}
}

void STOP_clicked(GtkWidget *button, gpointer data) {
	int find = 0;
	find = search(gates[8]);
	GtkWidget *image, *event;
	event = gtk_event_box_new ();
	image = gtk_image_new_from_file("OUTPUT_OFF.png");
	
	gtk_container_add (GTK_CONTAINER (event), image);
	gtk_layout_put (GTK_LAYOUT (layout), event, array[find].x, array[find].y);
	gtk_event_box_set_above_child(GTK_EVENT_BOX(event), FALSE);
	gtk_event_box_set_visible_window(GTK_EVENT_BOX(event),(gboolean)FALSE);
	gtk_widget_show (image);
	gtk_widget_show (event);
}

GtkWidget *create_bbox( gint horizontal, char *title, gint spacing, gint child_w, gint child_h, gint layout ) {
    	
	GtkWidget *frame;
	GtkWidget *button;
	GtkWidget *bbox;

      	frame = gtk_frame_new (title);

        bbox = gtk_vbutton_box_new ();

      	gtk_container_set_border_width (GTK_CONTAINER (bbox), 5);
      	gtk_container_add (GTK_CONTAINER (frame), bbox);

        gtk_button_box_set_layout (GTK_BUTTON_BOX (bbox), layout);
     	
     	button = gtk_button_new_with_label ("AND");
	gtk_container_add (GTK_CONTAINER (bbox), button);
      	g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(AND_clicked), NULL);
      	
      	button = gtk_button_new_with_label ("OR");
	gtk_container_add (GTK_CONTAINER (bbox), button);
      	g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(OR_clicked), NULL);
      	
      	button = gtk_button_new_with_label ("NOR");
	gtk_container_add (GTK_CONTAINER (bbox), button);
      	g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(NOR_clicked), NULL);
      	
      	button = gtk_button_new_with_label ("NOT");
	gtk_container_add (GTK_CONTAINER (bbox), button);
      	g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(NOT_clicked), NULL);
      	
      	button = gtk_button_new_with_label ("XOR");
	gtk_container_add (GTK_CONTAINER (bbox), button);
      	g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(XOR_clicked), NULL);
      	
      	button = gtk_button_new_with_label ("NAND");
	gtk_container_add (GTK_CONTAINER (bbox), button);
      	g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(NAND_clicked), NULL);
      	
      	button = gtk_button_new_with_label ("INPUT_ON");
	gtk_container_add (GTK_CONTAINER (bbox), button);
      	g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(INPUT_ON_clicked), NULL);
      	
      	button = gtk_button_new_with_label ("INPUT_OFF");
	gtk_container_add (GTK_CONTAINER (bbox), button);
      	g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(INPUT_OFF_clicked), NULL);
      	
      	button = gtk_button_new_with_label ("OUTPUT");
	gtk_container_add (GTK_CONTAINER (bbox), button);
      	g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(OUTPUT_clicked), NULL);
      	
      	button = gtk_button_new_with_label (" - WIRE");
	gtk_container_add (GTK_CONTAINER (bbox), button);
      	g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(HORI_WIRE_clicked), NULL);
      	
      	button = gtk_button_new_with_label (" | WIRE");
	gtk_container_add (GTK_CONTAINER (bbox), button);
      	g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(VERT_WIRE_clicked), NULL);

	button = gtk_button_new_with_label ("RUN");
	gtk_container_add (GTK_CONTAINER (bbox), button);
      	g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(RUN_clicked), NULL);

	button = gtk_button_new_with_label ("STOP");
	gtk_container_add (GTK_CONTAINER (bbox), button);
      	g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(STOP_clicked), NULL);

	
      	return(frame);
}

GdkPixbuf *create_pixbuf(const gchar * filename) {
	GdkPixbuf *pixbuf;
	GError *error = NULL;
    	pixbuf = gdk_pixbuf_new_from_file(filename, &error);
    	if(!pixbuf) {
      		fprintf(stderr, "%s\n", error->message);
       		g_error_free(error);
    	}
  	return pixbuf;
  	
}

void open_dialog(GtkWidget *button, gpointer window) {
	GtkWidget *dialog, *image, *event;
	int r;
	gint i = 5;
	const char *filename;
	GdkPixbuf *pixbuf;
	GError *error = NULL;
	dialog = gtk_file_chooser_dialog_new("Choose a file", GTK_WINDOW(window), GTK_FILE_CHOOSER_ACTION_OPEN, GTK_STOCK_OK, GTK_RESPONSE_OK, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);
	gtk_widget_show_all(dialog);
	r = gtk_dialog_run (GTK_DIALOG (dialog));
	switch (r) {
		case GTK_RESPONSE_OK:
			filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
      			gtk_widget_destroy (dialog);
      			break;
    		case GTK_RESPONSE_DELETE_EVENT:
    		case GTK_RESPONSE_CANCEL:
      			gtk_widget_destroy (dialog);
    		case GTK_RESPONSE_NONE:
     	 		return;
    	}
    	event = gtk_event_box_new ();
    	image = gtk_image_new_from_file(filename);
    	icons[i].image = image;
	icons[i].x = i*45;
	icons[i].y = i*45;
	icons[i].width = 50;
	icons[i].height = 50;

	gtk_container_add (GTK_CONTAINER (event), image);
	gtk_layout_put (GTK_LAYOUT (layout), event, i*50, i*50);
	gtk_event_box_set_above_child(GTK_EVENT_BOX(event), FALSE);
	g_signal_connect (G_OBJECT (event), "button_press_event", G_CALLBACK (handleClick), (gpointer) &icons[i]);
	gtk_event_box_set_visible_window(GTK_EVENT_BOX(event),(gboolean)FALSE);
	gtk_widget_show (image);
	gtk_widget_show (event);
  
    	pixbuf = gdk_pixbuf_new_from_file (filename, &error);
  	g_free (filename);
 	if (error) {
     		GtkWidget *msg;
     		msg = gtk_message_dialog_new (GTK_WINDOW (window), GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, error->message);
      		gtk_dialog_run (GTK_DIALOG (msg));
      		gtk_widget_destroy (msg);
      		g_error_free (error);
      		return;
      	}
}

void cw_new(GtkWidget *newMi, gpointer window) {
	new = 1;
}

void save_dialog(GtkWidget *saveMi, gpointer window) {
	GtkWidget *dialog;
	dialog = gtk_file_chooser_dialog_new ("Save File", window, GTK_FILE_CHOOSER_ACTION_SAVE, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, GTK_STOCK_SAVE, GTK_RESPONSE_ACCEPT, NULL);
	gtk_file_chooser_set_do_overwrite_confirmation (GTK_FILE_CHOOSER (dialog), TRUE);
	if (new == 1) {
		gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER (dialog), "/Home");
		gtk_file_chooser_set_current_name (GTK_FILE_CHOOSER (dialog), "Untitled document");
	}
	else
		gtk_file_chooser_set_filename (GTK_FILE_CHOOSER (dialog), "old");
	
	if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT) {
		char *filename;
		filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
		save_to_file (filename);
		g_free (filename);
	}
	gtk_widget_destroy (dialog);
}

static gboolean cw_delete(GtkWidget *window, gpointer data) {
	gtk_main_quit();
	return FALSE;
}

int main( int   argc, char *argv[]) {
      	static GtkWidget* window = NULL;
      	GtkWidget *main_vbox;
       	GtkWidget *hbox;
      	GtkWidget *box;
	GtkWidget *frame_vert;
       	GtkWidget *menubar;
	GtkWidget *fileMenu;
	GtkWidget *fileMi;
	GtkWidget *openMi;
	GtkWidget *saveMi;
	GtkWidget *quitMi;
	GtkWidget *newMi;
	
      	gtk_init( &argc, &argv );
//window
      	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   	gtk_window_set_title(GTK_WINDOW(window), "Logic Gate Simulator");
   	gtk_window_set_default_size(GTK_WINDOW(window), 1500, 1500);
   	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
   	gtk_container_set_border_width (GTK_CONTAINER (window), 10);
   	gtk_window_set_icon(GTK_WINDOW(window), create_pixbuf("icon.png"));

      	g_signal_connect (G_OBJECT (window), "destroy",	G_CALLBACK(gtk_main_quit), NULL);  
//layout      	
      	layout = gtk_layout_new(NULL, NULL);
	gtk_container_add(GTK_CONTAINER(window), layout);
	gtk_widget_show(layout);
//main_vbox
      	main_vbox = gtk_vbox_new (0, 0);
      	gtk_layout_put (GTK_LAYOUT (layout), main_vbox, 20, 9);
            
        frame_vert = gtk_frame_new ("Logic Gate Toolbar");
      	gtk_box_pack_start (GTK_BOX (main_vbox), frame_vert, TRUE, TRUE, 10);

      	hbox = gtk_hbox_new (FALSE, 0);
      	gtk_container_set_border_width (GTK_CONTAINER (hbox), 10);
      	gtk_container_add (GTK_CONTAINER (frame_vert), hbox);
	gtk_box_pack_start (GTK_BOX (hbox), create_bbox (FALSE, "", 5, 85, 20, GTK_BUTTONBOX_SPREAD), TRUE, TRUE, 0);
	gtk_layout_put (GTK_LAYOUT (layout), hbox, 24, 22);
//box
	box = gtk_hbox_new(0, 0);
	gtk_container_set_border_width (GTK_CONTAINER (box), 10);
	gtk_layout_put (GTK_LAYOUT (layout), box, 0, 0);
	gtk_widget_show (box);
//menubar	
	menubar = gtk_menu_bar_new();
	fileMenu = gtk_menu_new();
	
	fileMi = gtk_menu_item_new_with_label("File");
	openMi = gtk_menu_item_new_with_label("Open");
	saveMi = gtk_menu_item_new_with_label("Save");
	quitMi = gtk_menu_item_new_with_label("Quit");
	newMi = gtk_menu_item_new_with_label("New");

	gtk_menu_item_set_submenu(GTK_MENU_ITEM(fileMi), fileMenu);
	gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), newMi);
	gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), openMi);
	gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), saveMi);
	gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), quitMi);
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), fileMi);
	gtk_box_pack_start(GTK_BOX(box), menubar, 0, 0, 0);
//callback	
	g_signal_connect(G_OBJECT(newMi), "activate", G_CALLBACK(cw_new), NULL);
	g_signal_connect(G_OBJECT(openMi), "activate", G_CALLBACK(open_dialog), NULL);
	g_signal_connect(G_OBJECT(saveMi), "activate", G_CALLBACK(save_dialog), NULL);
	g_signal_connect(G_OBJECT(quitMi), "activate", G_CALLBACK(cw_delete), NULL);
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(cw_delete), NULL);
	
      	gtk_widget_show_all (window);
      
      	gtk_main ();
      	return(0);
}
