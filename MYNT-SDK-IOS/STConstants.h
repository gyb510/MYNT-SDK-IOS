//
//  STConstants.h
//  STMyntBluetooth
//
//  Created by gejw on 16/6/1.
//  Copyright © 2016年 Slightech. All rights reserved.
//

#ifndef STConstants_h
#define STConstants_h

#if TARGET_OS_IOS
#import <UIKit/UIKit.h>
#import <CoreBluetooth/CoreBluetooth.h>
#else
#import <IOBluetooth/IOBluetooth.h>
#import <CoreBluetooth/CoreBluetooth.h>
#endif

#define mynt_deprecated __attribute__((deprecated("deprecated and will be removed in the feture")))

typedef NS_ENUM(NSInteger, MYNTClickValue) {
    // if you set the values below, [mynt:didReceiveClickEvent:] will not invoked when you click mynt
    MYNTClickValueNone = 0x00,
    MYNTClickValueMusicPlay = 0x01,
    MYNTClickValueMusicNext = 0x02,
    MYNTClickValueMusicPrevious = 0x03,
    MYNTClickValueMusicVolumeUp = 0x04,
    MYNTClickValueMusicVolumeDown = 0x05,
    MYNTClickValueCameraShutter = 0x09,
    MYNTClickValueCameraBurst = 0x0A,
    MYNTClickValuePPTNextPage = 0x06,
    MYNTClickValuePPTPreviousPage = 0x07,
    MYNTClickValuePPTExit = 0x08,
    
    // if you set the values below, [mynt:didReceiveClickEvent:] will be invoked when you click mynt
    MYNTClickValuePhoneFlash    = 0xA0,
    MYNTClickValuePhoneAlarm    = 0xA1,
    MYNTClickValueAskHelp       = 0xA3,
    MYNTClickValueCustomClick   = 0xB0
};

typedef NS_ENUM(NSInteger, MYNTClickEvent) {
    MYNTClickEventClick = 0x01,
    MYNTClickEventDoubleClick = 0x02,
    MYNTClickEventTripleClick = 0x03,
    MYNTClickEventHold = 0x09,
    MYNTClickEventClickHold = 0x10,
    MYNTClickEventPhoneFlash = 0xA0,
    MYNTClickEventPhoneAlarm = 0xA1,
    MYNTClickEventPhoneAlarmOff = 0xA2
};

typedef NS_ENUM(NSInteger, MYNTInfoType) {
    MYNTInfoTypeManufaturer = 0x00,
    MYNTInfoTypeModel,
    MYNTInfoTypeSn,
    MYNTInfoTypeFirmware,
    MYNTInfoTypeHardware,
    MYNTInfoTypeSoftware,
};

typedef NS_ENUM(NSInteger, MYNTHardwareType) {
    MYNTHardwareTypeNone       = 0xFF,
    MYNTHardwareTypeMYNTV1     = 0x00,
    MYNTHardwareTypeMYNTV2     = 0x01,
    MYNTHardwareTypeMYNTGPS    = 0x02
};

typedef NS_ENUM(NSInteger, MYNTState) {
    MYNTStateDisconnected = 0x00,
    MYNTStateStartConnecting,
    MYNTStateConnecting,
    MYNTStateConnected,
};

#endif /* STConstants_h */

// MARK: =======================STMyntBluetoothDelegate=======================
@class STMyntBluetooth, STMynt, STPeripheral;

@protocol STMyntBluetoothDelegate <NSObject>

@optional

/**
 *  Invoked when the central manager's state has been updated.
 *
 *  @param myntBluetooth
 *  @param state         the current state of the bluetooth
 */
- (void)myntBluetooth:(STMyntBluetooth * _Nonnull)myntBluetooth didUpdateState:(CBCentralManagerState)state;

/**
 *  Invoked when the mynt has been discoverd.
 *
 *  @param myntBluetooth
 *  @param mynt
 */
- (void)myntBluetooth:(STMyntBluetooth * _Nonnull)myntBluetooth didDiscoverMynt:(STMynt * _Nonnull)mynt;

/**
 *  Invoked when the mynt has been discoverd timeout.
 *
 *  @param myntBluetooth
 *  @param mynt
 */
- (void)myntBluetooth:(STMyntBluetooth * _Nonnull)myntBluetooth didDiscoverTimeoutMynt:(STMynt * _Nonnull)mynt;

/**
 *  Invoked if sdk print log.
 *
 *  @param myntBluetooth
 *  @param sn            the sn of the mynt when the mynt is discoverd.
 *
 *  @return if this mynt need filter(don't ues it), so you can need true.
 */
- (void)myntBluetooth:(STMyntBluetooth * _Nonnull)myntBluetooth didPrintLog:(NSString * _Nonnull)log;

@end

// MARK: =======================STMyntDelegate=======================

@protocol STMyntDelegate <NSObject>

@optional

/**
 *  Invoked when the mynt has started to connect
 *
 *  @param mynt
 */
- (void)myntDidStartConnect:(STMynt * _Nonnull)mynt;

/**
 *  Invoked when a connection initiated has succeeded
 *
 *  @param mynt
 */
- (void)myntDidConnected:(STMynt * _Nonnull)mynt;

/**
 *  Invoked when a connection has been disconnected
 *
 *  @param mynt
 *  @param error
 */
- (void)mynt:(STMynt * _Nonnull)mynt didDisconnected:(NSError * _Nullable)error;

/**
 *  Invoked when the rssi of the mynt has been updated.
 *
 *  @param mynt
 *  @param RSSI the rssi of the mynt
 */
- (void)mynt:(STMynt * _Nonnull)mynt didUpdateRSSI:(NSInteger)RSSI;

/**
 *  Invoked when the battery of the mynt has been updated.
 *
 *  @param mynt
 *  @param battery the battery of the mynt
 */
- (void)mynt:(STMynt * _Nonnull)mynt didUpdateBattery:(NSArray <NSNumber *> * _Nonnull)batteries;

/**
 *  Invoked when the alarm state of the mynt has been updated.
 *
 *  @param mynt
 *  @param alarmState the alarm state of the mynt
 */
- (void)mynt:(STMynt * _Nonnull)mynt didUpdateAlarmState:(BOOL)isAlarm;

/**
 *  Invoked when the mynt is clicked
 *
 *  @param mynt
 *  @param clickEvent  the click type of the event (e.g. Click or Double Click)
 */
- (void)mynt:(STMynt * _Nonnull)mynt didReceiveClickEvent:(MYNTClickEvent)clickEvent;

/**
 *  Request the state if the mynt need autoconnect or not
 *
 *  @param mynt
 *
 *  @return is need autoconnect ?
 */
- (BOOL)didRequestAutoconnect:(STMynt * _Nonnull)mynt;

/**
 *  Invoked when the connection exception
 *
 *  @param mynt
 */
- (void)didNeedRestartBluetooth:(STMynt * _Nonnull)mynt;

@end

