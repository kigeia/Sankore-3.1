/*
 * UBSettings.h
 *
 *  Created on: Oct 29, 2008
 *      Author: luc
 */

#ifndef UBSETTINGS_H_
#define UBSETTINGS_H_

#include <QtCore>
#include <QtGui>
#include <QtNetwork>

#include "UB.h"
#include "UBSetting.h"

class UBSettings : public QObject
{

    Q_OBJECT;

    public:

        static UBSettings* settings()
        {
            if (!sSingleton)
                sSingleton = new UBSettings(qApp);

            return sSingleton;
        }

    private:

        UBSettings(QObject *parent = 0);
        virtual ~UBSettings();

    public:

        QStringList* supportedKeyboardSizes;
        void InitKeyboardPaletteKeyBtnSizes();
        void ValidateKeyboardPaletteKeyBtnSize();


        int penWidthIndex();

        qreal currentPenWidth();

        int penColorIndex();
        QColor currentPenColor();
        QColor penColor(bool onDarkBackground);
        QList<QColor> penColors(bool onDarkBackground);

        // Marker related
        int markerWidthIndex();
        qreal currentMarkerWidth();
        int markerColorIndex();
        QColor currentMarkerColor();
        QColor markerColor(bool onDarkBackground);
        QList<QColor> markerColors(bool onDarkBackground);

        // Eraser related
        int eraserWidthIndex();
        qreal eraserFineWidth();
        qreal eraserMediumWidth();
        qreal eraserStrongWidth();
        qreal currentEraserWidth();

        // Background related
        bool isDarkBackground();
        bool isCrossedBackground();
        void setDarkBackground(bool isDarkBackground);
        void setCrossedBackground(bool isCrossedBackground);

        // Stylus palette related
        bool isStylusPaletteVisible();

        // Text related
        QString fontFamily();
        void setFontFamily(const QString &family);
        int fontPixelSize();
        void setFontPixelSize(int pixelSize);
        bool isBoldFont();
        void setBoldFont(bool bold);
        bool isItalicFont();
        void setItalicFont(bool italic);

        void setPassword(const QString& id, const QString& password);
        QString password(const QString& id);
        void removePassword(const QString& id);

        QString proxyUsername();
        void setProxyUsername(const QString& username);
        QString proxyPassword();
        void setProxyPassword(const QString& password);

        QString communityUsername();
        void setCommunityUsername(const QString& username);
        QString communityPassword();
        void setCommunityPassword(const QString& password);

        void init();

        static QString uniboardDataDirectory();
        static QString uniboardDocumentDirectory();

        static QString libraryPaletteFavoriteListFilePath();
        static QString trashLibraryPaletteDirPath();

        QString uniboardShapeLibraryDirectory();
        QString uniboardGipLibraryDirectory();
        QString uniboardImageLibraryDirectory();
        QString uniboardUserImageDirectory();
        QString defaultUserImagesDirectory();

        QString uniboardUserVideoDirectory();
        QString uniboardDefaultUserImageLibraryDirectory();

        QString uniboardInteractiveUserDirectory();
        QString animationUserDirectory();
        QString uniboardInteractiveLibraryDirectory();
        QString uniboardInteractiveFavoritesDirectory();
        QString sankoreDistributedInteractiveDirectory();

        QString podcastRecordingDirectory();

        QNetworkProxy* httpProxy();

        static int pointerDiameter;
        static int boardMargin;

        static QColor crossDarkBackground;
        static QColor crossLightBackground;
        static QColor paletteColor;
        static QColor opaquePaletteColor;

        static QColor documentViewLightColor;

        static QBrush eraserBrushDarkBackground;
        static QBrush eraserBrushLightBackground;

        static QPen eraserPenDarkBackground;
        static QPen eraserPenLightBackground;

        static QColor documentSizeMarkColorDarkBackground;
        static QColor documentSizeMarkColorLightBackground;

        static int crossSize;
        static int colorPaletteSize;
        static int objectFrameWidth;

        static QString documentGroupName;
        static QString documentName;
        static QString documentSize;
        static QString documentIdentifer;
        static QString documentVersion;
        static QString documentUpdatedAt;

        static QString trashedDocumentGroupNamePrefix;

        static QString currentFileVersion;

        static QString uniboardDocumentNamespaceUri;
        static QString uniboardApplicationNamespaceUri;

        static const int maxThumbnailWidth;
        static const int defaultThumbnailWidth;

        static const int defaultImageWidth;
        static const int defaultShapeWidth;
        static const int defaultWidgetIconWidth;
        static const int defaultVideoWidth;
        static const int defaultGipWidth;
        static const int defaultSoundWidth;

        static const int thumbnailSpacing;

        static const qreal minScreenRatio;

        static QStringList bitmapFileExtensions;
        static QStringList vectoFileExtensions;
        static QStringList imageFileExtensions;
        static QStringList widgetFileExtensions;
        static QStringList interactiveContentFileExtensions;

        static QColor treeViewBackgroundColor;

        static int objectInControlViewMargin;

        static QString appPingMessage;

        static QString defaultDocumentGroupName;
        static QString documentTrashGroupName;

        UBSetting* uniboardWebUrl;
        UBSetting* productWebUrl;

        QString softwareUpdatesUrl;
        QString appRssUrl;
        QString softwareLibrariesUrl;
        QString softwareHomeUrl;
        QString oEmbedJsLibraryUrl;
        QString softwarePurchaseUrl;
        QString documentsPublishingUrl;
        QString capturesPublishingUrl;
        QString publishingAuthenticationUrl;
        QString documentPlayerScriptUrl;
        QString documentPlayerPageScriptUrl;
        QString documentPlayerCssUrl;

        UBSetting* appToolBarPositionedAtTop;
        UBSetting* appToolBarDisplayText;
        UBSetting* appEnableAutomaticSoftwareUpdates;
        UBSetting* appEnableSoftwareUpdates;
        UBSetting* appToolBarOrientationVertical;
        UBSetting* appEnableUniboardTransition;

        UBSetting* appIsInSoftwareUpdateProcess;

        UBSetting* appLastSessionDocumentUUID;
        UBSetting* appLastSessionPageIndex;

        UBSetting* boardPenFineWidth;
        UBSetting* boardPenMediumWidth;
        UBSetting* boardPenStrongWidth;

        UBSetting* boardMarkerFineWidth;
        UBSetting* boardMarkerMediumWidth;
        UBSetting* boardMarkerStrongWidth;

        UBSetting* boardPenPressureSensitive;
        UBSetting* boardMarkerPressureSensitive;

        UBSetting* boardUseHighResTabletEvent;

//        UBSetting* boardKeyboardPaletteAutoMinimize;
        UBSetting* boardKeyboardPaletteKeyBtnSize;

        UBColorListSetting* boardPenLightBackgroundColors;
        UBColorListSetting* boardPenLightBackgroundSelectedColors;

        UBColorListSetting* boardPenDarkBackgroundColors;
        UBColorListSetting* boardPenDarkBackgroundSelectedColors;

        UBSetting* boardMarkerAlpha;

        UBColorListSetting* boardMarkerLightBackgroundColors;
        UBColorListSetting* boardMarkerLightBackgroundSelectedColors;

        UBColorListSetting* boardMarkerDarkBackgroundColors;
        UBColorListSetting* boardMarkerDarkBackgroundSelectedColors;

        UBSetting* webUseExternalBrowser;
        UBSetting* webShowPageImmediatelyOnMirroredScreen;

        UBSetting* webHomePage;
        UBSetting* webBookmarksPage;
        UBSetting* webAddBookmarkUrl;
        UBSetting* webShowAddBookmarkButton;

        UBSetting* pageCacheSize;

        UBSetting* boardZoomFactor;

        UBSetting* mirroringRefreshRateInFps;

        UBSetting* lastImportFilePath;
        UBSetting* lastImportFolderPath;

        UBSetting* lastExportFilePath;
        UBSetting* lastExportDirPath;

        UBSetting* lastImportToLibraryPath;

        UBSetting* lastPicturePath;
        UBSetting* lastWidgetPath;
        UBSetting* lastVideoPath;

        UBSetting* appOnlineUserName;

        UBSetting* boardShowToolsPalette;

        QMap<DocumentSizeRatio::Enum, QSize> documentSizes;

        QSize defaultDocumentSize;

        UBSetting* svgViewBoxMargin;
        UBSetting* pdfMargin;
        UBSetting* pdfPageFormat;
        UBSetting* pdfResolution;

        UBSetting* podcastFramesPerSecond;
        UBSetting* podcastVideoSize;
        UBSetting* podcastWindowsMediaBitsPerSecond;
        UBSetting* podcastAudioRecordingDevice;
        UBSetting* podcastQuickTimeQuality;

        UBSetting* podcastPublishToYoutube;
        UBSetting* youTubeUserEMail;

        UBSetting* uniboardWebEMail;
        UBSetting* uniboardWebAuthor;
        UBSetting* uniboardWebGoogleMapApiKey;

        UBSetting* podcastPublishToIntranet;
        UBSetting* intranetPodcastPublishingUrl;
        UBSetting* intranetPodcastAuthor;

        UBSetting* favoritesNativeToolUris;

        //UBSetting* shouldShowBundleMessage;

        UBSetting* replyWWSerialPort;
        UBSetting* replyPlusConnectionURL;
        UBSetting* replyPlusAddressingMode;

        UBSetting* replyPlusMaxKeypads;

        UBSetting* documentThumbnailWidth;
        UBSetting* imageThumbnailWidth;
        UBSetting* videoThumbnailWidth;
        UBSetting* shapeThumbnailWidth;
        UBSetting* gipThumbnailWidth;
        UBSetting* soundThumbnailWidth;

        UBSetting* navigPaletteWidth;
        UBSetting* libPaletteWidth;

        UBSetting* communityUser;
        UBSetting* communityPsw;

        /*
        static int navigPaletteWidth;
        static int libPaletteWidth;
        */

    public slots:

        void setPenWidthIndex(int index);
        void setPenColorIndex(int index);

        void setMarkerWidthIndex(int index);
        void setMarkerColorIndex(int index);

        void setEraserWidthIndex(int index);
        void setEraserFineWidth(qreal width);
        void setEraserMediumWidth(qreal width);
        void setEraserStrongWidth(qreal width);

         void setStylusPaletteVisible(bool visible);

        void setPenPressureSensitive(bool sensitive);
        void setMarkerPressureSensitive(bool sensitive);

        QVariant value ( const QString & key, const QVariant & defaultValue = QVariant() ) const;
        void setValue (const QString & key,const QVariant & value);

        void colorChanged()
        {
            emit colorContextChanged();
        }

    signals:
        void colorContextChanged();

    private:

        QSettings* mAppSettings;
        QSettings* mUserSettings;

        static const int sDefaultFontPixelSize;
        static const char *sDefaultFontFamily;

    private:

        static QSettings* getAppSettings();

        static QPointer<QSettings> sAppSettings;
        static QPointer<UBSettings> sSingleton;

};


#endif /* UBSETTINGS_H_ */
