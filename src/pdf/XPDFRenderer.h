/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef XPDFRENDERER_H
#define XPDFRENDERER_H
#include <QImage>
#include "PDFRenderer.h"
#include <splash/SplashBitmap.h>
#include <xpdf/Object.h>
#include <xpdf/GlobalParams.h>
#include <xpdf/SplashOutputDev.h>
#include <xpdf/PDFDoc.h>

class PDFDoc;

class XPDFRenderer : public PDFRenderer
{
    Q_OBJECT

    public:
        XPDFRenderer(const QString &filename, bool importingFile = false);
        virtual ~XPDFRenderer();

        bool isValid() const;

        virtual int pageCount() const;

        virtual QSizeF pageSizeF(int pageNumber) const;

        virtual int pageRotation(int pageNumber) const;

        virtual QString title() const;

    public slots:
        void render(QPainter *p, int pageNumber, const QRectF &bounds = QRectF());

    private:
        void init();
        QImage* createPDFImage(int pageNumber, const qreal xscale = 0.5, const qreal yscale = 0.5, const QRectF &bounds = QRectF());

        PDFDoc *mDocument;
        static QAtomicInt sInstancesCount;
        qreal mSliceX;
        qreal mSliceY;

        SplashBitmap* mpSplashBitmap;
        SplashOutputDev* mSplash;
        qreal mScaleX;
        qreal mScaleY;
};

#endif // XPDFRENDERER_H
