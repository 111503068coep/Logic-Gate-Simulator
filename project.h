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

#ifndef __PROJECT_H
#define __PROJECT_H

#define ICON_BUFFER 5
#define INPUT_OFF 0
#define INPUT_ON 1
#define AND 10
#define OR 20
#define NOR 30
#define XOR 40
#define NAND 50
#define NOT 60

struct Icon {
	GtkWidget *image;
  	int x,y,width,height;
};

struct Icon icons[ICON_BUFFER];

typedef struct position {
	int x;
	int y;
	char *gate;
}position;
position array[512];

int AND_output(int input_1, int input_2);
int OR_output(int input_1, int input_2);
int NOT_output(int input_1);
int NAND_output(int input_1, int input_2);
int NOR_output(int input_1, int input_2);
int XOR_output(int input_1, int input_2);
int search(char *key);
int CALCULATE(void);
void save_to_file(char *filename);
static gboolean handleMove( GtkWidget *widget, GdkEventButton *event, gpointer data );
static gboolean handleRelease( GtkWidget *widget, GdkEventButton *event, gpointer data );
static gboolean handleClick( GtkWidget *widget, GdkEventButton *event, gpointer data );
void AND_clicked(GtkWidget *button, gpointer data);
void OR_clicked(GtkWidget *button, gpointer data);
void NOT_clicked(GtkWidget *button, gpointer data);
void NOR_clicked(GtkWidget *button, gpointer data);
void NAND_clicked(GtkWidget *button, gpointer data);
void XOR_clicked(GtkWidget *button, gpointer data);
void INPUT_ON_clicked(GtkWidget *button, gpointer data);
void INPUT_OFF_clicked(GtkWidget *button, gpointer data);
void OUTPUT_clicked(GtkWidget *button, gpointer data);
void HORI_WIRE_clicked(GtkWidget *button, gpointer data);
void VERT_WIRE_clicked(GtkWidget *button, gpointer data);
void RUN_clicked(GtkWidget *button, gpointer data);
void STOP_clicked(GtkWidget *button, gpointer data);
GtkWidget *create_bbox( gint horizontal, char *title, gint spacing, gint child_w, gint child_h, gint layout );
GdkPixbuf *create_pixbuf(const gchar * filename);
void open_dialog(GtkWidget *button, gpointer window);
void cw_new(GtkWidget *newMi, gpointer window);
void save_dialog(GtkWidget *saveMi, gpointer window);
static gboolean cw_delete(GtkWidget *window, gpointer data);
#endif
