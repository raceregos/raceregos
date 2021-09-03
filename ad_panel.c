/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <protectedKeys.h>
#include <pthread.h>
#include "KKDSClient.h"
#include "MainWindow.h"
#include "StatusPanel.h"
#include "PK.h"
#include "BSControl.h"

void setupPKPanel(GtkWidget *backPanel);
//----------------------------------------------------------------------------------------------------------------
GtkWidget *lblContrast,
    *lblBrightness,
    *lblText,
    *lblInUse; //??not used
GtkWidget *rbContrast[8],
    *rbBrightness[8],
    *txtAND[4],
    *brightnessBox,
    *contrastBox;
GList *rbContGroup;
GtkWidget *ANDPanel,
    *ANDGrid,
    *ANDBrightnessGrid,
    *PKPanel;
GtkWidget *setANDTextButton,
    *setANDBrightnessButton,
    *setANDContrastButton;

pBzWindowHandle bzWindowHandle = NULL;
pPkWindowHandle pkWindowHandle = NULL;
pAndWindowHandle andWindowHandle = NULL;
char hostName[32], hostIP[32], serverName[32], serverIP[32];
/*bool getConfig(char *fileName){
  char inpBuff[80];
    FILE *f = fopen(fileName, "rt");
    if (f == NULL) return false;
    while (!feof(f)){
       fgets(inpBuf, 80, f);
       if (strlen(inpBuf) > 1){
           if (strstr(inpBuf, "<HostName>") != NULL){
             if (strstr(inpBuf[strlen("<HostName>")+1], "</HostName>")!=NULL){
                
              }
           }
      }
   } 
}*/
//-----------------------------------------------------------------------------------------------

void setupANDPanel(GtkWidget *backPanel)
{
    int i;
    char outStr[16];
    printf("step 44\n");
    gtk_container_set_border_width(GTK_CONTAINER(backPanel), 4);
    gtk_widget_set_size_request(backPanel, 600, 250);
    printf("step 33\n");
    ANDGrid = gtk_grid_new();
    rbContrast[0] = gtk_radio_button_new_with_label(NULL, "Lev-1");
    gtk_grid_attach(GTK_GRID(ANDGrid), rbContrast[i], 0, 0, 1, 1);
    gtk_widget_show(rbContrast[0]);
    GSList *group = gtk_radio_button_get_group(GTK_RADIO_BUTTON(rbContrast[0]));
    lblContrast = gtk_label_new("Contrast");
    gtk_fixed_put((GtkFixed *)backPanel, lblContrast, 20, 10);
    for (i = 1; i < 8; i++)
    {
        sprintf(outStr, "Lev-%d", i + 1);
        group = gtk_radio_button_get_group(GTK_RADIO_BUTTON(rbContrast[i - 1]));
        rbContrast[i] = gtk_radio_button_new_with_label(group, outStr);
        gtk_grid_attach(GTK_GRID(ANDGrid), rbContrast[i], i % 4, i / 4, 1, 1);
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(rbContrast[i]), FALSE);
        gtk_widget_show(rbContrast[i]);
    }
    ANDBrightnessGrid = gtk_grid_new();
    rbBrightness[0] = gtk_radio_button_new_with_label(NULL, "Lev-1");
    gtk_grid_attach(GTK_GRID(ANDBrightnessGrid), rbBrightness[0], 0, 0, 1, 1);
    gtk_widget_show(rbBrightness[0]);
    lblBrightness = gtk_label_new("Brightness");
    gtk_fixed_put((GtkFixed *)backPanel, lblBrightness, 20, 60);
    GSList *brightnessGroup = gtk_radio_button_get_group(GTK_RADIO_BUTTON(rbBrightness[0]));
    g_signal_connect(rbBrightness[0], "clicked", G_CALLBACK(applyRBBrightnessCmd), (gpointer)NULL);
    gtk_widget_show(rbBrightness[0]);
    for (i = 1; i < 8; i++)
    {
        sprintf(outStr, "Lev-%d", i + 1);
        brightnessGroup = gtk_radio_button_get_group(GTK_RADIO_BUTTON(rbBrightness[i - 1]));
        rbBrightness[i] = gtk_radio_button_new_with_label(brightnessGroup, outStr);
        gtk_grid_attach(GTK_GRID(ANDBrightnessGrid), rbBrightness[i], i % 4, i / 4, 1, 1);
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(rbBrightness[i]), FALSE);
        g_signal_connect(rbBrightness[i], "clicked", G_CALLBACK(applyRBBrightnessCmd), (gpointer)NULL);
        gtk_widget_show(rbBrightness[i]);
    }
    gtk_fixed_put((GtkFixed *)backPanel, ANDGrid, 200, 10);
    gtk_fixed_put((GtkFixed *)backPanel, ANDBrightnessGrid, 200, 60);

    lblText = gtk_label_new("Text");
    gtk_fixed_put((GtkFixed *)backPanel, lblText, 20, 110);
    for (i = 0; i < 4; i++)
    {
        txtAND[i] = gtk_entry_new();
        gtk_entry_set_text((GtkEntry *)txtAND[i], "Sample Text");
        gtk_fixed_put((GtkFixed *)backPanel, txtAND[i], 200, 110 + i * 34);
        gtk_widget_show(txtAND[i]);
    }

    setANDContrastButton = gtk_button_new_with_label("Apply Contrast");
    gtk_widget_set_size_request(setANDContrastButton, 150, 30);
    gtk_fixed_put((GtkFixed *)backPanel, setANDContrastButton, 480, 20);
    gtk_widget_show(setANDContrastButton);
    g_signal_connect(setANDContrastButton, "clicked", G_CALLBACK(applyRBContrastCmd), (gpointer)NULL);

    setANDBrightnessButton = gtk_button_new_with_label("Apply Brightness");
    gtk_widget_set_size_request(setANDBrightnessButton, 150, 30);
    gtk_fixed_put((GtkFixed *)backPanel, setANDBrightnessButton, 480, 70);
    gtk_widget_show(setANDBrightnessButton);
    g_signal_connect(setANDBrightnessButton, "clicked", G_CALLBACK(applyRBBrightnessCmd), (gpointer)NULL);

    setANDTextButton = gtk_button_new_with_label("Apply Text");
    gtk_widget_set_size_request(setANDTextButton, 150, 30);
    gtk_fixed_put((GtkFixed *)backPanel, setANDTextButton, 480, 160);
    gtk_widget_show(setANDTextButton);
    g_signal_connect(setANDTextButton, "clicked", G_CALLBACK(applyTxtCmd), (gpointer)NULL);
}
void setupPKPanel(GtkWidget *backPanel)
{
}
bool kkdsClientConnect(void)
{
    setupAndConnection();
    setupBzConnection();
    setupBsConnection();
    setupPkConnection();
    setupStConnection();

    andWindowHandle->error = andInitialize(&andWindowHandle->andHandle, andWindowHandle->serverHostname,
                                           NULL, NULL, andWindowHandle->clientIPAddress);
    if (andWindowHandle->error != AND_SUCCESS)
    {
        printf("ERROR RSLT : %s\n", (char *)andErrorString(andWindowHandle->error));
        exit(0);
    }
    bzWindowHandle->error = bzInitialize(&bzWindowHandle->bzHandle, bzWindowHandle->serverHostname,
                                         NULL, NULL, bzWindowHandle->clientIPAddress);
    if (bzWindowHandle->error != BZ_SUCCESS)
    {
        printf("ERROR RSLT : %s\n", (char *)bzErrorString(bzWindowHandle->error));
        exit(0);
    }
    bsWindowHandle->error = bsInitialize(&bsWindowHandle->bsHandle, bsWindowHandle->serverHostname,
                                         NULL, NULL, bsWindowHandle->clientIPAddress);
    if (bsWindowHandle->error != BS_SUCCESS)
    {
        printf("ERROR RSLT : %s\n", (char *)bsErrorString(bsWindowHandle->error));
        exit(0);
    }

    pkWindowHandle->error = pkInitialize(&pkWindowHandle->pkHandle, pkWindowHandle->serverIPAddress,
                                         NULL, NULL, pkWindowHandle->clientIPAddress);
    if (pkWindowHandle->error != PK_SUCCESS)
    {
        printf("ERROR RSLT : %s\n", (char *)pkErrorString(pkWindowHandle->error));
        exit(0);
    }

    stWindowHandle->error = stInitialize(&stWindowHandle->stHandle, stWindowHandle->serverIPAddress,
                                         NULL, NULL, stWindowHandle->clientIPAddress);
    if (stWindowHandle->error != ST_SUCCESS)
    {
        printf("ERROR RSLT : %s\n", (char *)stErrorString(stWindowHandle->error));
        exit(0);
    }

    pkWindowHandle->error = pkSetPressEventCBFunction(pkWindowHandle->pkHandle, pkPress);
    pkWindowHandle->error = pkSetReleaseEventCBFunction(pkWindowHandle->pkHandle, pkRelease);

    pthread_create((pthread_t *)&clientThreadHandle,
                   NULL,
                   clientThreadFunction,
                   NULL);

    return true;
}

void applyRBBrightnessCmd(GtkWidget *widget, gpointer data)
{
    int brightnessIndex = getBrightnessBtnGroupSelectedId();
    if (brightnessIndex != -1)
    {
        unsigned char bright = brightnessIndex;
        gdk_threads_add_idle((GSourceFunc)postBrightnessReq, (void *)(&bright));
    }
}

void applyRBContrastCmd(GtkWidget *widget, gpointer data)
{
    int contrastIndex = getContrastBtnGroupSelectedId();
    if (contrastIndex != -1)
    {
        unsigned char contrast = contrastIndex;
        gdk_threads_add_idle((GSourceFunc)postContrastReq, (void *)(&contrast));
    }
}

void applyTxtCmd(GtkWidget *widget, gpointer data)
{
    gdk_threads_add_idle((GSourceFunc)postTextUpdateReq, (void *)"Deneme Text");
}

void postTextUpdateReq(void *data)
{
    andWindowHandle->error = andClientUseOn(andWindowHandle->andHandle);
    andWindowHandle->error = andSetText(andWindowHandle->andHandle, (AndRow)1, (char *)data);
    andWindowHandle->error = andClientUseOff(andWindowHandle->andHandle);
}

bool postBrightnessReq(void *data)
{
    unsigned char *bVal = (unsigned char *)data;
    unsigned char k = *bVal;
    andWindowHandle->error = andSetBrightness(andWindowHandle->andHandle, (AndBrightness)k);
    return false;
}

bool postContrastReq(void *data)
{
    unsigned char *bVal = (unsigned char *)data;
    unsigned char k = *bVal;
    andWindowHandle->error = andSetContrast(andWindowHandle->andHandle, (AndContrast)k);
    //printf("Result of Contrast set : %s", (char *) andErrorString(andWindowHandle->error));
    return false;
}

int getBrightnessBtnGroupSelectedId()
{
    for (int i = 0; i < 8; i++)
    {
        if (gtk_toggle_button_get_active((GtkToggleButton *)rbBrightness[i]))
            return i + 1;
    }
    return -1;
}

int getContrastBtnGroupSelectedId()
{
    for (int i = 0; i < 8; i++)
    {
        if (gtk_toggle_button_get_active((GtkToggleButton *)rbContrast[i]))
            return i + 1;
    }
    return -1;
}
//**********************************************************************************************************************************************

void setupAndConnection()
{
    andWindowHandle = (pAndWindowHandle)malloc(sizeof(AndWindowHandle));
    andWindowHandle->state = 0;
    andWindowHandle->quit = 0;
    andWindowHandle->andInformationRun = 0;
    andWindowHandle->serverHostname = (char *)malloc((size_t)STRING_LENGTH);
    bzero((void *)andWindowHandle->serverHostname, (size_t)STRING_LENGTH);
    andWindowHandle->serverIPAddress = (char *)malloc((size_t)STRING_LENGTH);
    bzero((void *)andWindowHandle->serverIPAddress, (size_t)STRING_LENGTH);
    andWindowHandle->clientHostname = (char *)malloc((size_t)STRING_LENGTH);
    bzero((void *)andWindowHandle->clientHostname, (size_t)STRING_LENGTH);
    andWindowHandle->clientIPAddress = (char *)malloc((size_t)STRING_LENGTH);
    bzero((void *)andWindowHandle->clientIPAddress, (size_t)STRING_LENGTH);
    andWindowHandle->andHandle = NULL;
    andWindowHandle->errorString = NULL;
    andWindowHandle->error = AND_SUCCESS;
    andWindowHandle->debugOn = 0;
    strcpy(andWindowHandle->serverIPAddress, "10.1.10.119");
    strcpy(andWindowHandle->serverHostname, "10.1.10.119");
    strcpy(andWindowHandle->clientIPAddress, "10.1.10.200");
    strcpy(andWindowHandle->clientHostname, "bangtte");
}
//

void setupBzConnection()
{
    bzWindowHandle = (pBzWindowHandle)malloc(sizeof(BzWindowHandle));
    bzWindowHandle->state = 0;
    bzWindowHandle->quit = 0;
    bzWindowHandle->bzInformationRun = 0;
    bzWindowHandle->serverHostname = (char *)malloc((size_t)STRING_LENGTH);
    bzero((void *)bzWindowHandle->serverHostname, (size_t)STRING_LENGTH);
    bzWindowHandle->serverIPAddress = (char *)malloc((size_t)STRING_LENGTH);
    bzero((void *)bzWindowHandle->serverIPAddress, (size_t)STRING_LENGTH);
    bzWindowHandle->clientHostname = (char *)malloc((size_t)STRING_LENGTH);
    bzero((void *)bzWindowHandle->clientHostname, (size_t)STRING_LENGTH);
    bzWindowHandle->clientIPAddress = (char *)malloc((size_t)STRING_LENGTH);
    bzero((void *)bzWindowHandle->clientIPAddress, (size_t)STRING_LENGTH);
    bzWindowHandle->bzHandle = NULL;
    bzWindowHandle->errorString = NULL;
    bzWindowHandle->error = BZ_SUCCESS;
    bzWindowHandle->silent = 0;

    strcpy(bzWindowHandle->serverIPAddress, "10.1.10.119");
    strcpy(bzWindowHandle->serverHostname, "10.1.10.119");
    strcpy(bzWindowHandle->clientIPAddress, "10.1.10.200");
    strcpy(bzWindowHandle->clientHostname, "bangtte");
}

void setupBsConnection()
{
    bsWindowHandle = (pBsWindowHandle)malloc(sizeof(BsWindowHandle));
    bsWindowHandle->state = 0;
    bsWindowHandle->quit = 0;
    bsWindowHandle->bsLocal = 0;
    bsWindowHandle->bsInformationRun = 0;
    bsWindowHandle->serverHostname = (char *)malloc((size_t)STRING_LENGTH);
    bzero((void *)bsWindowHandle->serverHostname, (size_t)STRING_LENGTH);
    bsWindowHandle->serverIPAddress = (char *)malloc((size_t)STRING_LENGTH);
    bzero((void *)bsWindowHandle->serverIPAddress, (size_t)STRING_LENGTH);
    bsWindowHandle->clientHostname = (char *)malloc((size_t)STRING_LENGTH);
    bzero((void *)bsWindowHandle->clientHostname, (size_t)STRING_LENGTH);
    bsWindowHandle->clientIPAddress = (char *)malloc((size_t)STRING_LENGTH);
    bzero((void *)bsWindowHandle->clientIPAddress, (size_t)STRING_LENGTH);
    bsWindowHandle->bsHandle = NULL;
    bsWindowHandle->errorString = NULL;
    bsWindowHandle->error = BS_SUCCESS;
    bsWindowHandle->debugOn = 0;
    bsWindowHandle->pressRelease = 0;

    strcpy(bsWindowHandle->serverIPAddress, "10.1.10.119");
    strcpy(bsWindowHandle->serverHostname, "10.1.10.119");
    strcpy(bsWindowHandle->clientIPAddress, "10.1.10.200");
    strcpy(bsWindowHandle->clientHostname, "bangtte");
}

void setupPkConnection()
{
    unsigned char i;
    pkWindowHandle = (pPkWindowHandle)malloc(sizeof(PkWindowHandle));
    pkWindowHandle->state = 0;
    pkWindowHandle->quit = 0;
    pkWindowHandle->pkInformationRun = 0;
    for (i = 0; i < 16; i++)
    {
        pkWindowHandle->pkStatus[i] = 0;
        pkWindowHandle->pkEventNumber[i] = 0;
    }
    pkWindowHandle->serverHostname = (char *)malloc((size_t)STRING_LENGTH);
    bzero((void *)pkWindowHandle->serverHostname, (size_t)STRING_LENGTH);
    pkWindowHandle->serverIPAddress = (char *)malloc((size_t)STRING_LENGTH);
    bzero((void *)pkWindowHandle->serverIPAddress, (size_t)STRING_LENGTH);
    pkWindowHandle->clientHostname = (char *)malloc((size_t)STRING_LENGTH);
    bzero((void *)pkWindowHandle->clientHostname, (size_t)STRING_LENGTH);
    pkWindowHandle->clientIPAddress = (char *)malloc((size_t)STRING_LENGTH);
    bzero((void *)pkWindowHandle->clientIPAddress, (size_t)STRING_LENGTH);
    pkWindowHandle->pkHandle = NULL;
    pkWindowHandle->errorString = NULL;
    pkWindowHandle->error = PK_SUCCESS;
    pkWindowHandle->debugOn = 0;
    //printf("Start thread .7.\n");

    strcpy(pkWindowHandle->serverIPAddress, "10.1.10.119");
    strcpy(pkWindowHandle->serverHostname, "10.1.10.119");
    strcpy(pkWindowHandle->clientIPAddress, "10.1.10.200");
    strcpy(pkWindowHandle->clientHostname, "bangtte");
}

void *clientThreadFunction(void *arg)
{

    testCounter = 0;
    char outStr[32];
    unsigned char i;

    do
    {
        testCounter++;
        sleep(1);
        gdk_threads_add_idle((GSourceFunc)postPeriodicTempStatusCmd, (void *)NULL);
        gdk_threads_add_idle((GSourceFunc)postPeriodicHumidityStatusCmd, (void *)NULL);
        gdk_threads_add_idle((GSourceFunc)postPeriodicFanStatusCmd, (void *)NULL);
        gdk_threads_add_idle((GSourceFunc)postPeriodicUPSStatusCmd, (void *)NULL);
        gdk_threads_add_idle((GSourceFunc)postPeriodicPKStatusCmd, (void *)NULL);
        gdk_threads_add_idle((GSourceFunc)postPeriodicBSStatusCmd, (void *)NULL);
        if (testCounter % 5 == 0)
            gdk_threads_add_idle((GSourceFunc)postResourceUtil, (void *)NULL);

    } while (andWindowHandle->quit < 255);

    if (andWindowHandle->andInformationRun > 0)
        andFinalize(&(andWindowHandle->andHandle));
    if (bzWindowHandle->bzInformationRun > 0)
        bzFinalize(&(bzWindowHandle->bzHandle));
    if (bsWindowHandle->bsInformationRun > 0)
        bsFinalize(&(bsWindowHandle->bsHandle));
    if (pkWindowHandle->pkInformationRun > 0)
        pkFinalize(&(pkWindowHandle->pkHandle));
    if (stWindowHandle->stInformationRun > 0)
        stFinalize(&(stWindowHandle->stHandle));
    printf("Thread is stopped\n");
    return NULL;
}
void stopThread(void *data)
{
    andWindowHandle->quit = 255;
}
