diff --git a/algo.hpp b/algo.hpp
index a565e20..d6f3734 100644
--- a/algo.hpp
+++ b/algo.hpp
@@ -1,9 +1,10 @@
 #ifndef ALGO_HPP
 #define ALGO_HPP
 
+#include<QObject>
 #include<opencv2/opencv.hpp>
 
-class Algo{
+class Algo: public QObject {
     Q_OBJECT
 public:
     explicit Algo(int _r = 35):radius(_r){
@@ -13,6 +14,8 @@ private:
 private slots :
     void DrawCricle(cv::Mat& img,int x,int y){
         cv::circle(img,cv::Point(x,y),radius,cv::Scalar(255,255,255));
+        cv::namedWindow("debug");
+        cv::imshow("debug",img);
         emit refrush(img);
     }
 signals :
diff --git a/mainwindow.cpp b/mainwindow.cpp
index 0700b4b..de1a824 100644
--- a/mainwindow.cpp
+++ b/mainwindow.cpp
@@ -56,6 +56,7 @@ void MainWindow::mousePressEvent(QMouseEvent *event){
 }
 
 void MainWindow::frush(cv::Mat& result){
+
     QImage img = ConvertImage(result);
     ui->label->setPixmap(QPixmap::fromImage(img));
     ui->label->resize(ui->label->pixmap()->size());
diff --git a/mainwindow.h b/mainwindow.h
index bdd2a50..5ad3643 100644
--- a/mainwindow.h
+++ b/mainwindow.h
@@ -25,13 +25,14 @@ signals:
 private slots:
     void on_pushButton_2_clicked();
     void on_pushButton_clicked();
+    void frush(cv::Mat&);
 
 private:
     Ui::MainWindow *ui;
     Algo* algo;
     cv::Mat image,result;
     void mousePressEvent(QMouseEvent *);
-    void frush(cv::Mat&);
+
 };
 
 #endif // MAINWINDOW_H
