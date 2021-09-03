/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <gtk/gtk.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <string.h>

#include "MainWindow.h"
#include "StatusPanel.h"
#include "KKDSClient.h"
#include "TestBuzzer.h"
#include "PK.h"
#include "BSControl.h"
#include "KKDSClient.h"
static bool pkConnectionAvail = false;
GtkWidget *mainWindow,
    *notebook,
    *mainContainer,
    *fixedFrame1,
    *fixedFrame2,
    *tabLabel,
    *pkPanel,
    *bzPanel,
    //*bsPanel,
    *bsFrame,
    *testButton;
GtkWidget *cpuLabel,
    *cpuLabelVal,
    *memoryUsageLabel,
    *memoryUsageLabelVal;
double startTime = 0;

static void deleteWnd(GtkWidget *widget, GtkWidget *event, gpointer data)
{
    stopThread(NULL);
    //
    sleep(5);
    gtk_main_quit();
}

bool postResourceUtil(void *data)
{

    char *cmd = "ps -u";

    char buf[128];
    char par1[16],
        par2[16],
        par3[16],
        par4[16];
    char outStr[32];
    FILE *fp;

    if ((fp = popen(cmd, "r")) == NULL)
    {
        printf("Error opening pipe!\n");
        return false;
    }

    while (fgets(buf, 128, fp) != NULL)
    {
        // Do whatever you want here...
        if (strstr(buf, "kkdstest") != NULL)
        {
            sscanf(buf, "%s%s%s%s",
                   par1, par2, par3, par4);
            sprintf(outStr, "%c %s", '%', par3);
            gtk_label_set_text((GtkLabel *)cpuLabelVal, outStr);
            sprintf(outStr, "%c %s", '%', par4);
            gtk_label_set_text((GtkLabel *)memoryUsageLabelVal, outStr);
        }
    }

    if (pclose(fp))
    {
        //printf("Command not found or exited with error status\n");
        return false;
    }
    return false;
}
void setupGUI()
{
    int i;
    char outStr[16];
    mainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    g_signal_connect(mainWindow, "delete-event", G_CALLBACK(deleteWnd), NULL);

    gtk_container_set_border_width(GTK_CONTAINER(mainWindow), 2);
    gtk_widget_set_size_request(mainWindow, 600, 800);
    mainContainer = gtk_fixed_new();
    gtk_widget_set_size_request(mainContainer, 600, 800);
    fixedFrame1 = gtk_fixed_new();
    gtk_container_set_border_width(GTK_CONTAINER(fixedFrame1), 4);

    fillStatusPanel((GtkWidget *)fixedFrame1);

    gtk_fixed_put((GtkFixed *)mainContainer, fixedFrame1, 4, 4);
    gtk_container_add(GTK_CONTAINER(mainWindow), mainContainer);
    gtk_widget_override_background_color(mainWindow, GTK_STATE_FLAG_NORMAL, &fwidgetColor[CLBLACK]);

    //-------------------------------------------------------------******************************************************************
    notebook = gtk_notebook_new();
    gtk_notebook_set_tab_pos(GTK_NOTEBOOK(notebook), GTK_POS_TOP);
    gtk_widget_override_background_color(notebook, GTK_STATE_FLAG_NORMAL, &fwidgetColor[CLGRAY]);
    gtk_widget_set_size_request(mainWindow, 600, 150);
    gtk_fixed_put((GtkFixed *)mainContainer, (GtkWidget *)notebook, 4, 504);
    gtk_widget_show(notebook);

    fixedFrame2 = gtk_fixed_new();
    gtk_container_set_border_width(GTK_CONTAINER(fixedFrame2), 4);
    gtk_widget_set_size_request(fixedFrame2, 600, 250);
    tabLabel = gtk_label_new(titleArray[0]);

    cpuLabel = gtk_label_new("CPU UTIL");
    gtk_widget_set_size_request(cpuLabel, 100, 28);
    gtk_fixed_put((GtkFixed *)fixedFrame2, cpuLabel, 20, 20);

    cpuLabelVal = gtk_label_new("000");
    gtk_widget_set_size_request(cpuLabelVal, 100, 28);
    gtk_fixed_put((GtkFixed *)fixedFrame2, cpuLabelVal, 130, 20);

    memoryUsageLabel = gtk_label_new("MEM UTIL");
    gtk_widget_set_size_request(memoryUsageLabel, 100, 28);
    gtk_fixed_put((GtkFixed *)fixedFrame2, memoryUsageLabel, 20, 60);

    memoryUsageLabelVal = gtk_label_new("00");
    gtk_widget_set_size_request(memoryUsageLabelVal, 100, 28);
    gtk_fixed_put((GtkFixed *)fixedFrame2, memoryUsageLabelVal, 130, 60);
    //gtk_frame_set_shadow_type((GtkFrame*)bgFrame,   GTK_SHADOW_ETCHED_IN);
    //gtk_widget_set_size_request(bgFrame, 590,290);
    gtk_widget_override_color(tabLabel, GTK_STATE_FLAG_NORMAL, &fwidgetColor[CLWHITE]);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), fixedFrame2, tabLabel);
    //------------------------------------------------------- AND Param settings
    ANDPanel = gtk_fixed_new();
    GtkWidget *tabLabel2 = gtk_label_new(titleArray[1]);
    setupANDPanel(ANDPanel);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), ANDPanel, tabLabel2);
    //---------------------------------------------------------------------------------------
    PKPanel = gtk_fixed_new();
    GtkWidget *tabLabel3 = gtk_label_new(titleArray[2]);
    setUpPKInterface(PKPanel);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), PKPanel, tabLabel3);
    //--------------------------------------------------------------------------
    bzPanel = gtk_fixed_new();
    GtkWidget *tabLabel4 = gtk_label_new("Buzzer");
    setupBuzzerGUI(bzPanel);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), bzPanel, tabLabel4);
    //--------------------------------------------------------------------------
    bsFrame = gtk_frame_new("aaaa");
    gtk_frame_set_shadow_type((GtkFrame *)bsFrame, GTK_SHADOW_ETCHED_IN);
    gtk_widget_set_size_request(bsFrame, 590, 290);
    //gtk_fixed_put((GtkFixed*)bsPanel, bsFrame, 5,5);
    GtkWidget *tabLabel5 = gtk_label_new("BattleShort");

    //    setupBSGUI(bsPanel);
    setupBSGUI(bsFrame);
    //gtk_container_add(GTK_CONTAINER(bsFrame), bsPanel);

    //gtk_widget_show(bsFrame);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), bsPanel, tabLabel5);
    //--------------------------------------------------------------------------

    gtk_widget_show(fixedFrame1);
    gtk_widget_show(ANDPanel);
    gtk_widget_show(bzPanel);
    gtk_widget_show(mainContainer);
    gtk_widget_show_all(mainWindow);
    gtk_notebook_set_current_page(GTK_NOTEBOOK(notebook), 0);
    //Connect to server
    kkdsClientConnect();
    //
}
static void test_callback(GtkWidget *widget, gpointer data)
{
    //printf("Counter will be reset\n");
    gdk_threads_add_idle((GSourceFunc)stopThread, data);
}
void setPKColor(int key, KKDS_STATE state)
{
    int i = 27 + key;
    gtk_widget_override_background_color(statusLabels[i].widget,
                                         GTK_STATE_FLAG_NORMAL,
                                         &fwidgetColor[state]);
}

void updateGUI(void *key)
{
    char outStr[32];
    int *b = (int *)key;
    sprintf(outStr, "Key Value generated : %d", *b);
    gtk_label_set_text(GTK_LABEL(testLabel), outStr);
}