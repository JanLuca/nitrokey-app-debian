//
// Created by sz on 14.01.17.
//

#ifndef NITROKEYAPP_TRAY_H
#define NITROKEYAPP_TRAY_H

#define TRAY_MSG_TIMEOUT 5000

#include <QObject>
enum trayMessageType { INFORMATION, WARNING, CRITICAL };

namespace Ui {
    class Tray;
}

#include <QMutex>
class tray_Worker : public QObject
{
Q_OBJECT

public:
    QMutex mtx;

public slots:
    void doWork();

signals:
    void resultReady();
    void progress(int i);
};

#include <QSystemTrayIcon>
#include <QAction>
#include <memory>
#include "StorageActions.h"

class Tray : public QObject {
Q_OBJECT


public:
  void setAdmin_mode(bool _admin_mode);
  void setDebug_mode(bool _debug_mode);
  Tray(QObject * _parent, bool _debug_mode, bool _extended_config, StorageActions *actions);
    virtual ~Tray();
    void showTrayMessage(QString message);
    void showTrayMessage(const QString &title, const QString &msg, enum trayMessageType type = INFORMATION,
                         int timeout = TRAY_MSG_TIMEOUT);
  public slots:
    void regenerateMenu();
    void updateOperationInProgressBar(int p);

  signals:
    void progress(int i);


private slots:
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void generateMenuPasswordSafe();
    void populateOTPPasswordMenu();
    void passOTPProgressFurther(int i);
    void showOTPProgressInTray(int i);

private:
    Q_DISABLE_COPY(Tray);
    virtual bool eventFilter(QObject *obj, QEvent *event) override;
    void generateMenu(bool init=false, std::function<void(QMenu *)> run_before = [](QMenu*){});
    void generateMenuForStorageDevice();
    void generatePasswordMenu();
    void generateMenuForProDevice();
    void initActionsForStick10();
    void initActionsForStick20();
    void initCommonActions();
    int UpdateDynamicMenuEntrys(void);
    void createIndicator();

    QObject *main_window;
    QObject *storageActions;
    bool debug_mode;
    bool ExtendedConfigActive;

    QSystemTrayIcon *trayIcon;
    std::shared_ptr<QMenu> trayMenu;
    QMenu *trayMenuSubConfigure;
    std::shared_ptr<QMenu> trayMenuPasswdSubMenu;
//    QMenu *trayMenuTOTPSubMenu;
//    QMenu *trayMenuHOTPSubMenu;
    QMenu *trayMenuSubSpecialConfigure;

    QAction *quitAction;
    QAction *configureAction;
    QAction *resetAction;
    QAction *configureActionStick20;
    QAction *DebugAction;
    QAction *ActionAboutDialog;
//    QAction *SecPasswordAction;
//    QAction *Stick20SetupAction;
    QAction *Stick10ActionChangeUserPIN;
    QAction *Stick10ActionChangeAdminPIN;
    QAction *LockDeviceAction;
    QAction *UnlockPasswordSafeAction;

    QAction *Stick20ActionEnableCryptedVolume;
    QAction *Stick20ActionDisableCryptedVolume;
    QAction *Stick20ActionEnableHiddenVolume;
    QAction *Stick20ActionDisableHiddenVolume;
    QAction *Stick20ActionChangeUserPIN;
    QAction *Stick20ActionChangeAdminPIN;
    QAction *Stick20ActionChangeUpdatePIN;
    QAction *Stick20ActionEnableFirmwareUpdate;
    QAction *Stick20ActionExportFirmwareToFile;
    QAction *Stick20ActionDestroyCryptedVolume;
    QAction *Stick20ActionInitCryptedVolume;
    QAction *Stick20ActionFillSDCardWithRandomChars;
    QAction *Stick20ActionGetStickStatus;
    QAction *Stick20ActionUpdateStickStatus;
    QAction *Stick20ActionSetReadonlyUncryptedVolume;
    QAction *Stick20ActionSetReadWriteUncryptedVolume;
    QAction *Stick20ActionDebugAction;
    QAction *Stick20ActionSetupHiddenVolume;
    QAction *Stick20ActionClearNewSDCardFound;
    QAction *Stick20ActionLockStickHardware;
    QAction *Stick20ActionResetUserPassword;

  void destroyThread();

  tray_Worker *worker;
  QSignalMapper *mapper_TOTP;
  QSignalMapper *mapper_HOTP;
  QSignalMapper *mapper_PWS;
};


#endif //NITROKEYAPP_TRAY_H
