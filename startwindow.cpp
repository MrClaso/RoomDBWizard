#include "startwindow.h"
#include "ui_startwindow.h"
#include "tablewindow.h"
#include "ui_tablewindow.h"

StartWindow::StartWindow(QWidget *parent)
    : QDialog(parent)
    , startUi(new Ui::StartWindow)
{
    startUi->setupUi(this);
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
        QLabel *tableLabel = new QLabel();
        tableLabel->setText(tableDialog->tableName);
        startUi->verticalLayout->addWidget(tableLabel);
    }
}

void StartWindow::on_buttonBox_accepted()
{

    std::string dataBaseStr, DataBaseStr, tableNameStr, TableNameStr;
    dataBaseStr = startUi->lineEdit->text().toStdString();
    DataBaseStr = dataBaseStr;
    DataBaseStr[0] = toupper(DataBaseStr[0]);

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

    myfile.open(startUi->lineEdit_2->text().toStdString() + "/app/src/main/res/layout/activity_main.xml");
    
    myfile << "<?xml version=\"1.0\" encoding=\"utf-8\"?>";

myfile << "<!-- Copyright 2017 Google Inc.";
myfile << "";
myfile << "Licensed under the Apache License, Version 2.0 (the \"License\");";
myfile << "you may not use this file except in compliance with the License.";
myfile << "You may obtain a copy of the License at";
myfile << "";
    myfile << "http://www.apache.org/licenses/LICENSE-2.0";
myfile << "";
myfile << "Unless required by applicable law or agreed to in writing, software";
myfile << "distributed under the License is distributed on an \"AS IS\" BASIS,";
myfile << "WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.";
myfile << "See the License for the specific language governing permissions and";
myfile << "limitations under the License. -->";
myfile << "";
myfile << "<!-- Uses the Empty Activity Template.";
myfile << "Want to minimize unrelated busy work where students just remove code.";
myfile << "So, we are leaving the template code in. -->";
myfile << "";
myfile << "<androidx.constraintlayout.widget.ConstraintLayout";
    myfile << "xmlns:android=\"http://schemas.android.com/apk/res/android\"";
    myfile << "xmlns:app=\"http://schemas.android.com/apk/res-auto\"";
    myfile << "xmlns:tools=\"http://schemas.android.com/tools\"";
    myfile << "android:layout_width=\"match_parent\"";
    myfile << "android:layout_height=\"match_parent\"";
    myfile << "tools:context=\".MainActivity\">";
myfile << "";
    myfile << "<androidx.recyclerview.widget.RecyclerView";
        myfile << "android:id=\"@+id/recyclerview\"";
        myfile << "android:layout_width=\"0dp\"";
        myfile << "android:layout_height=\"0dp\"";
        myfile << "tools:listitem=\"@layout/recyclerview_item\"";
        myfile << "android:padding=\"@dimen/big_padding\"";
        myfile << "app:layout_constraintBottom_toBottomOf=\"parent\"";
        myfile << "app:layout_constraintLeft_toLeftOf=\"parent\"";
        myfile << "app:layout_constraintRight_toRightOf=\"parent\"";
        myfile << "app:layout_constraintTop_toTopOf=\"parent\" />";
myfile << "";
    myfile << "<com.google.android.material.floatingactionbutton.FloatingActionButton";
        myfile << "android:id=\"@+id/fab\"";
        myfile << "app:layout_constraintBottom_toBottomOf=\"parent\"";
        myfile << "app:layout_constraintEnd_toEndOf=\"parent\"";
        myfile << "android:layout_width=\"wrap_content\"";
        myfile << "android:layout_height=\"wrap_content\"";
        myfile << "android:layout_margin=\"16dp\"";
        myfile << "android:contentDescription=\"@string/add_word\"";
        myfile << "android:src=\"@drawable/ic_add_black_24dp\"/>";
myfile << "";
myfile << "</androidx.constraintlayout.widget.ConstraintLayout>";

myfile.close();
}

void StartWindow::on_pushButton_2_clicked()
{
    dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 "/home/clas/Development/Android_Studio_Projects",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);
    startUi->lineEdit_2->setText(dir);
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
