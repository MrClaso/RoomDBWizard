#include "startwindow.h"
#include "ui_startwindow.h"
#include "tablewindow.h"
#include "ui_tablewindow.h"

#include <QMessageBox>

StartWindow::StartWindow(QWidget *parent)
    : QDialog(parent)
    , startUi(new Ui::StartWindow)
{
    /*
 *     startUi->lineEdit->setStyleSheet("QLineEdit {  border: 2px solid;"
                                     "border-radius: 5px;}");
*/

    startUi->setupUi(this);

    startUi->widget->setStyleSheet("border: 2px solid grey");
    path_calculated = false;
}

StartWindow::~StartWindow()
{
    delete startUi;
}


void StartWindow::on_pushButton_clicked()
{
    if(!path_calculated) calculate_path();
    tableDialog = new TableWindow(this);
    tableDialog->setData(startUi->lineEdit->text());
    tableDialog->dir = startUi->lineEdit_2->text();
    tableDialog->package = package;
    tableDialog->package_as_path = package_as_path;

    tableDialog->setModal(true);

    if(tableDialog->exec() == QDialog::Accepted) { //Check if they clicked Ok
        QHBoxLayout *hL = new QHBoxLayout ();
        QLabel *tableLabel = new QLabel();
        QCheckBox *chBoxMakeTable = new QCheckBox();
        tableLabel->setText(tableDialog->tableName);
        hL->addWidget(tableLabel);
        hL->addStretch();
        hL->addWidget(chBoxMakeTable);
        startUi->verticalLayout->addLayout(hL);

        table.tableName = tableDialog->tableName;
        table.columnPaketList = tableDialog->columnPaketList;
        table.makeTable = chBoxMakeTable;
        tableList.append(table);
    }
}

void StartWindow::on_buttonBox_accepted()
{

    dataBaseStr = startUi->lineEdit->text().toStdString();
    DataBaseStr = dataBaseStr;
    DataBaseStr[0] = toupper(DataBaseStr[0]);

    ok = f1();

    ok = f2();

    ok = f3();

    ok = f4();

    ok = f5();

    ok = f6();


}

void StartWindow::on_pushButton_2_clicked()
{
    dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                            "/home/clas/Development/Android_Studio_Projects",
                                            QFileDialog::ShowDirsOnly
                                            | QFileDialog::DontResolveSymlinks);
    startUi->lineEdit_2->setText(dir);
}

bool StartWindow::f1(){
    myfile.open (startUi->lineEdit_2->text().toStdString() + "/app/src/main/java/" + package_as_path + "/" + DataBaseStr +"RoomDatabase.java");

    myfile << "package " << package << ";\n\n";
    myfile << "import android.content.Context;\n";
    myfile << "\n";
    myfile << "import androidx.annotation.NonNull;\n";
    myfile << "import androidx.room.Database;\n";
    myfile << "import androidx.room.Room;\n";
    myfile << "import androidx.room.RoomDatabase;\n";
    myfile << "import androidx.sqlite.db.SupportSQLiteDatabase;\n";
    myfile << "\n";
    myfile << "import java.util.concurrent.ExecutorService;\n";
    myfile << "import java.util.concurrent.Executors;\n";
    myfile << "\n";
    myfile << "@Database(entities = {";

    /*
    QList<QLabel*>::iterator it;
    QList<QLabel*> list = startUi->verticalLayoutWidget->findChildren<QLabel *>();
    it = list.begin();
    tableNameStr = it[0]->text().toStdString();
    TableNameStr = tableNameStr;
    TableNameStr[0] = toupper(TableNameStr[0]);

    myfile << TableNameStr << ".class" ;

    for( int i = 1; i < list.count(); i++){
        myfile << ", " << it[i]->text().toStdString() << ".class" ;
    }
    myfile << "}, version = 1, exportSchema = false)\n";
    myfile << "public abstract class " << DataBaseStr << "RoomDatabase extends RoomDatabase {\n";
    myfile << "\n";

    for( auto listIt : list)  {
        tableNameStr = listIt->text().toStdString();
        TableNameStr = tableNameStr;
        TableNameStr[0] = toupper(TableNameStr[0]);
        myfile << "public abstract ";
        myfile << TableNameStr << "Dao " << tableNameStr << "Dao();\n";
    }
*/


    it = tableList.begin();
    //    tableNameStr = it[0]->text().toStdString();
    tableNameStr = it[0].tableName.toStdString();

    TableNameStr = tableNameStr;
    TableNameStr[0] = toupper(TableNameStr[0]);


    QMessageBox msgBox;
    msgBox.setText("hej!");
    msgBox.exec();

    myfile << TableNameStr << ".class" ;

    for( int i = 1; i < tableList.count(); i++){
        myfile << ", " << it[i].tableName.toStdString() << ".class" ;
    }
    myfile << "}, version = 1, exportSchema = false)\n";
    myfile << "public abstract class " << DataBaseStr << "RoomDatabase extends RoomDatabase {\n";
    myfile << "\n";

    foreach (TableStruct listIt, tableList){

//    for( auto listIt : layoutList)  {
        tableNameStr = listIt.tableName.toStdString();
        TableNameStr = tableNameStr;
        TableNameStr[0] = toupper(TableNameStr[0]);
        myfile << "public abstract ";
        myfile << TableNameStr << "Dao " << tableNameStr << "Dao();\n";
    }
    myfile << "\n";
    myfile << "private static volatile " << DataBaseStr << "RoomDatabase INSTANCE;\n";
    myfile << "private static final int NUMBER_OF_THREADS = 4;\n";
    myfile << "static final ExecutorService databaseWriteExecutor =\n";
    myfile << "Executors.newFixedThreadPool(NUMBER_OF_THREADS);\n";
    myfile << "\n";
    myfile << "\tstatic " << DataBaseStr << "RoomDatabase getDatabase(final Context context) {\n";
    myfile << "\t\tif (INSTANCE == null) {\n";
    myfile << "\t\t\tsynchronized (" << DataBaseStr << "RoomDatabase.class) {\n";
    myfile << "\t\t\t\tif (INSTANCE == null) {\n";
    myfile << "\t\t\t\t\tINSTANCE = Room.databaseBuilder(context.getApplicationContext(),\n";
    myfile << "\t\t\t\t\t\t" << DataBaseStr << "RoomDatabase.class, \"" << dataBaseStr << "_database\")\n";
    myfile << "\t\t\t\t\t\t.addCallback(sRoomDatabaseCallback)\n";
    myfile << "\t\t\t\t\t\t.allowMainThreadQueries()\n";
    myfile << "\t\t\t\t\t\t.build();\n";
    myfile << "}\n";
    myfile << "}\n";
    myfile << "}\n";
    myfile << "return INSTANCE;\n";
    myfile << "}\n";
    myfile << "\n";
    myfile << "private static RoomDatabase.Callback sRoomDatabaseCallback = new RoomDatabase.Callback() {\n";
    myfile << "@Override\n";
    myfile << "public void onOpen(@NonNull SupportSQLiteDatabase db) {\n";
    myfile << "super.onOpen(db);\n";
    myfile << "}\n";
    myfile << "};\n";
    myfile << "}\n";

    myfile.close();

    return true;
}

bool StartWindow::f2(){


myfile.open(startUi->lineEdit_2->text().toStdString() + "/build.gradle", std::ios::app);

myfile << "\n\next {\n";
myfile << "appCompatVersion = '1.2.0'\n";
myfile << "constraintLayoutVersion = '2.0.2'\n";
myfile << "coreTestingVersion = '2.1.0'\n";
myfile << "lifecycleVersion = '2.2.0'\n";
myfile << "materialVersion = '1.2.1'\n";
myfile << "roomVersion = '2.2.5'\n";
myfile << "// testing\n";
myfile << "junitVersion = '4.13.1'\n";
myfile << "espressoVersion = '3.1.0'\n";
myfile << "androidxJunitVersion = '1.1.2'\n";

myfile << "}";

myfile.close();

return true;
}

bool StartWindow::f3(){

    iofile.open(startUi->lineEdit_2->text().toStdString() + "/app/build.gradle");

    std::string str(std::istreambuf_iterator<char>{iofile}, {});

    int start = str.find("dependencies {");
    int end = str.find("}", start +1);
    str.replace(start+15,end- start -15,"    implementation \"androidx.appcompat:appcompat:$rootProject.appCompatVersion\"\n"
                "implementation \"androidx.room:room-runtime:$rootProject.roomVersion\"\n"
                "annotationProcessor \"androidx.room:room-compiler:$rootProject.roomVersion\"\n"
                "androidTestImplementation \"androidx.room:room-testing:$rootProject.roomVersion\"\n"
                "// Lifecycle components\n"
                "implementation \"androidx.lifecycle:lifecycle-viewmodel:$rootProject.lifecycleVersion\"\n"
                "implementation \"androidx.lifecycle:lifecycle-livedata:$rootProject.lifecycleVersion\"\n"
                "implementation \"androidx.lifecycle:lifecycle-common-java8:$rootProject.lifecycleVersion\"\n\n"

                "// UI\n"
                "implementation \"androidx.constraintlayout:constraintlayout:$rootProject.constraintLayoutVersion\"\n"
                "implementation \"com.google.android.material:material:$rootProject.materialVersion\"\n\n"

                "// Testing\n"
                "testImplementation \"junit:junit:$rootProject.junitVersion\"\n"
                "androidTestImplementation \"androidx.arch.core:core-testing:$rootProject.coreTestingVersion\"\n"
                "androidTestImplementation (\"androidx.test.espresso:espresso-core:$rootProject.espressoVersion\", {\n"
                    "exclude group: 'com.android.support', module: 'support-annotations'\n"
                "})\n"
                "androidTestImplementation \"androidx.test.ext:junit:$rootProject.androidxJunitVersion\"\n"
);

    iofile.close();

    myfile.open(startUi->lineEdit_2->text().toStdString() + "/app/build.gradle");
    myfile << str;
    myfile.close();


return true;
}

bool StartWindow::f4(){
    myfile.open(startUi->lineEdit_2->text().toStdString() + "/app/src/main/res/layout/activity_main.xml");

    myfile << "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n";
    myfile << "<RelativeLayout xmlns:android=\"http://schemas.android.com/apk/res/android\"\n";
    myfile << "    xmlns:app=\"http://schemas.android.com/apk/res-auto\"\n";
    myfile << "    xmlns:tools=\"http://schemas.android.com/tools\"\n";
    myfile << "    android:layout_width=\"match_parent\"\n";
    myfile << "    android:layout_height=\"match_parent\"\n";
    myfile << "    android:padding=\"8dp\"\n";
    myfile << "    tools:context=\".MainActivity\">\n";
    myfile << "    <LinearLayout\n";
    myfile << "        android:layout_width=\"match_parent\"\n";
    myfile << "        android:layout_height=\"wrap_content\"\n";
    myfile << "        android:orientation=\"vertical\">\n";
    myfile << "\n";
    myfile << "        <LinearLayout\n";
    myfile << "            android:layout_width=\"match_parent\"\n";
    myfile << "            android:layout_height=\"wrap_content\"\n";
    myfile << "            android:orientation=\"horizontal\">\n";
    myfile << "\n";
    myfile << "            <TextView\n";
    myfile << "                android:layout_width=\"0dp\"\n";
    myfile << "                android:layout_height=\"wrap_content\"\n";
    myfile << "                android:layout_weight=\"30\"\n";
    myfile << "                android:text=\"Column 1\" />\n";
    myfile << "\n";
    myfile << "        </LinearLayout>\n";
    myfile << "\n";
    myfile << "        <androidx.recyclerview.widget.RecyclerView\n";
    myfile << "        android:id=\"@+id/recyclerview_item\"\n";
    myfile << "        android:layout_width=\"match_parent\"\n";
    myfile << "        android:layout_height=\"match_parent\" />\n";
    myfile << "    </LinearLayout>\n";
    myfile << "\n";
    myfile << "</RelativeLayout>\n";
    myfile.close();
return true;
}

bool StartWindow::f5(){

    myfile.open(startUi->lineEdit_2->text().toStdString() + "/app/src/main/res/layout/recyclerview_item.xml");

    myfile << "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n";
    myfile << "<RelativeLayout xmlns:android=\"http://schemas.android.com/apk/res/android\"\n";
        myfile << "android:layout_width=\"match_parent\"\n";
        myfile << "android:layout_height=\"wrap_content\"\n";
        myfile << "android:padding=\"0dp\">\n";
myfile << "    \n";
myfile << "    \n";
myfile << "    \n";
    myfile << "<androidx.cardview.widget.CardView\n";
            myfile << "android:layout_width=\"match_parent\"\n";
            myfile << "android:layout_height=\"wrap_content\"\n";
            myfile << "android:layout_marginBottom=\"3dp\">\n";
myfile << "    \n";
        myfile << "<LinearLayout\n";
            myfile << "android:id=\"@+id/linearLayoutDay\"\n";
            myfile << "android:layout_width=\"match_parent\"\n";
            myfile << "android:layout_height=\"wrap_content\"\n";
            myfile << "android:orientation=\"horizontal\"\n";
            myfile << "android:paddingStart=\"0dp\"\n";
            myfile << "android:paddingLeft=\"0dp\"\n";
            myfile << "android:paddingTop=\"15dp\"\n";
            myfile << "android:paddingEnd=\"0dp\"\n";
            myfile << "android:paddingRight=\"0dp\"\n";
            myfile << "android:paddingBottom=\"15dp\">\n";
myfile << "    \n";
            myfile << "<TextView\n";
                myfile << "android:id=\"@+id/textViewDate\"\n";
                myfile << "android:layout_width=\"0dp\"\n";
                myfile << "android:layout_height=\"wrap_content\"\n";
                myfile << "android:layout_weight=\"35\"\n";
                myfile << "android:textAlignment=\"viewStart\"\n";
                myfile << "android:textAppearance=\"@style/TextAppearance.AppCompat.Medium\" />\n";
myfile << "    \n";
        myfile << "</LinearLayout>\n";
myfile << "    \n";
        myfile << "</androidx.cardview.widget.CardView>\n";
myfile << "    \n";
    myfile << "</RelativeLayout>\n";

    myfile.close();

return true;
}

bool StartWindow::f6(){

return true;
}


void StartWindow::calculate_path(){
    iofile.open(startUi->lineEdit_2->text().toStdString() + "/app/src/main/AndroidManifest.xml");

    std::string str(std::istreambuf_iterator<char>{iofile}, {});
    iofile.close();

    int start = str.find("package=\"");
    int end = str.find("\"", start +9);
    package = str.substr(start+9,end- start -9);
    myfile.open(startUi->lineEdit_2->text().toStdString() + "/package.pack");
    myfile << package;
    package_as_path = package;
    int pos;
    pos = package_as_path.find(".");
    while (pos != -1 ) {
        package_as_path.replace(pos, 1 ,"/");
        pos = package_as_path.find(".", pos + 1);

    }
    myfile << "\n\n" << package_as_path;
    myfile.close();

    path_calculated = true;
}
