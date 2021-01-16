#include "tablewindow.h"
#include "ui_tablewindow.h"
#include "startwindow.h"

TableWindow::TableWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TableWindow)
{

    ui->setupUi(this);


    checkBoxDelete = new QCheckBox ();
    lEColumnName = new QLineEdit ();
    comboBoxType = new QComboBox ();
    checkBoxPrimary = new QCheckBox ();
    checkBoxUniqe = new QCheckBox ();
    checkBoxAI = new QCheckBox();
    hL = new QHBoxLayout ();

    comboBoxType->addItem(comboBoxOption3String, 3);
    comboBoxType->addItem(comboBoxOption1String, 1);
    comboBoxType->addItem(comboBoxOption2String, 2);

    lEColumnName->setFixedWidth(170);
    hL->addSpacing(10);
    hL->addWidget(checkBoxDelete);
    hL->addSpacing(12);

    hL->addWidget(lEColumnName);
    hL->addSpacing(10);

    hL->addWidget(comboBoxType);
    hL->addSpacing(10);

    hL->addWidget(checkBoxPrimary);
    hL->addWidget(checkBoxAI);
    hL->addWidget(checkBoxUniqe);

    hL->addStretch();

    ui->verticalLayout_2->addLayout(hL);

    column.del = checkBoxDelete;
    column.name = lEColumnName;
    column.type = comboBoxType;
    column.primary = checkBoxPrimary;
    column.unique = checkBoxUniqe;
    column.AI = checkBoxAI;

    columnList.append(column);
}


TableWindow::~TableWindow()
{
    delete ui;
}

void TableWindow::setData(QString dBaseName){
    this->dBaseName = dBaseName;
}

void TableWindow::on_pushButton_2_clicked()
{
    ColumnPaket *columnPaket = new ColumnPaket();
    columnPaket->colName = lEColumnName->text();
    columnPaket->colType = comboBoxType->currentData();
    columnPaketList.append(*columnPaket);

    checkBoxDelete = new QCheckBox ();
    lEColumnName = new QLineEdit ();
    comboBoxType = new QComboBox ();
    checkBoxPrimary = new QCheckBox ();
    checkBoxUniqe = new QCheckBox ();
    checkBoxAI = new QCheckBox();
    hL = new QHBoxLayout ();

    comboBoxType->addItem(comboBoxOption3String, 3);
    comboBoxType->addItem(comboBoxOption1String, 1);
    comboBoxType->addItem(comboBoxOption2String, 2);

    lEColumnName->setFixedWidth(170);
    hL->addSpacing(10);
    hL->addWidget(checkBoxDelete);
    hL->addSpacing(12);

    hL->addWidget(lEColumnName);
    hL->addSpacing(10);

    hL->addWidget(comboBoxType);
    hL->addSpacing(10);

    hL->addWidget(checkBoxPrimary);
    hL->addWidget(checkBoxAI);
    hL->addWidget(checkBoxUniqe);
    hL->addStretch();

    ui->verticalLayout_2->addLayout(hL);

    column.del = checkBoxDelete;
    column.name = lEColumnName;
    column.type = comboBoxType;
    column.primary = checkBoxPrimary;
    column.unique = checkBoxUniqe;
    column.AI = checkBoxAI;

    columnList.append(column);

}


void TableWindow::on_pushButton_clicked()
{
    std::string prim_str, type_str, colNameStr, ColNameStr, TableNameStr, DBaseNameStr;

    ColumnPaket *columnPaket = new ColumnPaket();
    columnPaket->colName = lEColumnName->text();
    columnPaket->colType = comboBoxType->currentData();
    columnPaketList.append(*columnPaket);

    tableName = ui->lineEdit->text();

    std::string tableNameStr = ui->lineEdit->text().toStdString();
    TableNameStr = tableNameStr;
    TableNameStr[0] = toupper(tableNameStr[0]);
    std::ofstream myfile;
    myfile.open (dir.toStdString() + "/app/src/main/java/" + package_as_path + "/" + TableNameStr +".java");

    myfile << "package " << package << ";\n";
    myfile << "\n\nimport androidx.room.ColumnInfo;\n";
    myfile << "import androidx.room.Entity;\n";
    myfile << "import androidx.room.Index;\n";
    myfile << "import androidx.room.PrimaryKey;\n\n";

    myfile << "@Entity(tableName = \"" << ui->lineEdit->text().toStdString() << "\"";

    int numUnique = 0;
    foreach (columnStruct i, columnList) {
        if( i.unique->isChecked()){
            if( numUnique == 0)
                myfile << ", indices = {@Index(value = \"" << i.name->text().toStdString() << "\", unique = true)";
            else
                myfile << ", @Index(value = \"" << i.name->text().toStdString() << "\", unique = true)";
            numUnique++;
        }
    }
    if( numUnique > 0)     myfile << "}";

    myfile << ")\n";

    myfile << "public class " << TableNameStr << " {\n\n";

    foreach (columnStruct i, columnList) {
        if(i.primary->isChecked()){
            myfile << "@PrimaryKey";
            if(i.AI->isChecked()){
                myfile << "(autoGenerate = true)";
            }
            myfile << "\n";

        }
        myfile << "@ColumnInfo(name = \"" << i.name->text().toStdString() << "\")\n";
        myfile << "private " << i.type->currentText().toStdString() << " " << i.name->text().toStdString() << ";\n\n";


    }

    myfile << "\n\n/*\n";
    myfile << "* Getters and Setters\n";
    myfile << "* */\n";

    foreach (columnStruct i, columnList) {
        colNameStr = i.name->text().toStdString();
        ColNameStr = colNameStr;
        ColNameStr[0] = toupper(colNameStr[0]);
        myfile << "public " << i.type->currentText().toStdString() << " get" << ColNameStr << "(){\n";
        myfile << "    return " << colNameStr << ";\n";
        myfile << "}\n";
        myfile << "public void set" << ColNameStr << "(" << i.type->currentText().toStdString() << " " << colNameStr << ") {\n";
        myfile << "   this." << colNameStr << " = " << colNameStr << ";\n";
        myfile << "}\n\n";
    }
    myfile << "}";

    myfile.close();

    myfile.open (dir.toStdString() + "/app/src/main/java/" + package_as_path + "/" + TableNameStr +"Dao.java");

    myfile << "package " << package << ";\n";
    myfile << "\n\n";
    myfile << "import androidx.lifecycle.LiveData;\n";
    myfile << "import androidx.room.Dao;\n";
    myfile << "import androidx.room.Delete;\n";
    myfile << "import androidx.room.Insert;\n";
    myfile << "import androidx.room.Query;\n";
    myfile << "import androidx.room.Update;\n";
    myfile << "\n";
    myfile << "import java.util.List;\n";
    myfile << "\n";
    myfile << "@Dao\n";
    myfile << "public interface " << TableNameStr <<"Dao {\n";
    myfile << "\n";
    myfile << "\n";
    myfile << "@Query(\"SELECT * FROM " << tableNameStr << "\")\n";
    myfile << "LiveData<List<" << TableNameStr << ">> getAll" << TableNameStr << "s();\n";
    myfile << "\n";
    myfile << "\n";
    myfile << "@Insert\n";
    myfile << "void insert(" << TableNameStr << " " << tableNameStr <<");\n";
    myfile << "\n";
    myfile << "@Delete\n";
    myfile << "void delete(" << TableNameStr << " " << tableNameStr <<");\n";
    myfile << "\n";
    myfile << "@Update\n";
    myfile << "void update(" << TableNameStr << " " << tableNameStr <<");\n";
    myfile << "\n";
    myfile << "}\n";
    myfile.close();

    DBaseNameStr = dBaseName.toStdString();
    DBaseNameStr[0] = toupper(DBaseNameStr[0]);

    myfile.open(dir.toStdString() + "/app/src/main/java/" + package_as_path + "/" + TableNameStr + "Repository.java");

    myfile << "package " << package << ";\n\n";

    myfile << "import android.app.Application;\n";
    myfile << "import android.database.sqlite.SQLiteConstraintException;\n";
    myfile << "import androidx.lifecycle.LiveData;\n";
    myfile << "import java.util.List;\n";
    myfile << "public class " << TableNameStr << "Repository {\n";
    myfile << "private final " << TableNameStr << "Dao m" << TableNameStr << "Dao;\n";
    myfile << "private final LiveData<List<" << TableNameStr << ">> mAll" << TableNameStr <<"s;\n";
    myfile << "// Note that in order to unit test the WordRepository, you have to remove the Application\n";
    myfile << "// dependency. This adds complexity and much more code, and this sample is not about testing.\n";
    myfile << "// See the BasicSample in the android-architecture-components repository at\n";
    myfile << "// https://github.com/googlesamples\n";
    myfile << TableNameStr << "Repository(Application application) {\n";
    myfile << DBaseNameStr << "RoomDatabase db = "<< DBaseNameStr << "RoomDatabase.getDatabase(application);\n";
    myfile << "m" << TableNameStr << "Dao = db." << tableNameStr << "Dao();\n";
    myfile << "mAll" << TableNameStr << "s = m" << TableNameStr << "Dao.getAll" << TableNameStr << "s();\n";
    myfile << "\n";
    myfile << "\n";
    myfile << "}\n";
    myfile << "\n";
    myfile << "// Room executes all queries on a separate thread.\n";
    myfile << "// Observed LiveData will notify the observer when the data has changed.\n";
    myfile << "LiveData<List<" << TableNameStr << ">> getAll" << TableNameStr << "s() {\n";
    myfile << "return mAll" << TableNameStr << "s;\n";
    myfile << "}\n";
    myfile << "\n";
    myfile << "// You must call this on a non-UI thread or your app will throw an exception. Room ensures\n";
    myfile << "// that you're not doing any long running operations on the main thread, blocking the UI.\n";
    myfile << "void insert(" << TableNameStr << " " << tableNameStr << ") {\n";
    myfile << "" << DBaseNameStr << "RoomDatabase.databaseWriteExecutor.execute(() -> {\n";
    myfile << "\n";
    myfile << "try{\n";
    myfile << "m" << TableNameStr << "Dao.insert(" << tableNameStr << ");\n";
    myfile << "}\n";
    myfile << "catch (SQLiteConstraintException ignored){\n";
    myfile << "}\n";
    myfile << "\n";
    myfile << "});\n";
    myfile << "}\n";
    myfile << "\n";
    myfile << "void update(" << TableNameStr << " " << tableNameStr << ") {\n";
    myfile << "" << DBaseNameStr << "RoomDatabase.databaseWriteExecutor.execute(() -> m" << TableNameStr << "Dao.update(" << tableNameStr << "));\n";
    myfile << "}\n";
    myfile << "\n";
    myfile << "void delete(" << TableNameStr << " " << tableNameStr << ") {\n";
    myfile << "" << DBaseNameStr << "RoomDatabase.databaseWriteExecutor.execute(() -> m" << TableNameStr << "Dao.delete(" << tableNameStr << "));\n";
    myfile << "}\n";
    myfile << "\n";
    myfile << "}\n";
    myfile.close();

    myfile.open(dir.toStdString() + "/app/src/main/java/" + package_as_path + "/" + TableNameStr + "ViewModel.java");

    myfile << "package " << package << ";\n\n";
    myfile << "import android.app.Application;\n";
    myfile << "\n";
    myfile << "import androidx.lifecycle.AndroidViewModel;\n";
    myfile << "import androidx.lifecycle.LiveData;\n";
    myfile << "\n";
    myfile << "import java.util.List;\n";
    myfile << "\n";
    myfile << "public class " << TableNameStr << "ViewModel extends AndroidViewModel {\n";
    myfile << "\n";
    myfile << "private final " << TableNameStr << "Repository m" << TableNameStr << "Repository;\n";
    myfile << "\n";
    myfile << "private final LiveData<List<" << TableNameStr << ">> mAll" << TableNameStr << "s;\n";
    myfile << "\n";
    myfile << "public " << TableNameStr << "ViewModel(Application application) {\n";
    myfile << "super(application);\n";
    myfile << "\n";
    myfile << "m" << TableNameStr << "Repository = new " << TableNameStr << "Repository(application);\n";
    myfile << "\n";
    myfile << "mAll" << TableNameStr << "s = m" << TableNameStr << "Repository.getAll" << TableNameStr << "s();\n";
    myfile << "}\n";
    myfile << "LiveData<List<" << TableNameStr << ">> getAll" << TableNameStr << "s() {\n";
    myfile << "return mAll" << TableNameStr << "s;\n";
    myfile << "}\n";
    myfile << "\n";
    myfile << "public void insert(" << TableNameStr << " " << tableNameStr << ") {\n";
    myfile << "m" << TableNameStr << "Repository.insert(" << tableNameStr << ");\n";
    myfile << "}\n";
    myfile << "\n";
    myfile << "public void update(" << TableNameStr << " " << tableNameStr << ") {\n";
    myfile << "m" << TableNameStr << "Repository.update(" << tableNameStr << ");\n";
    myfile << "}\n";
    myfile << "\n";
    myfile << "public void delete(" << TableNameStr << " " << tableNameStr << ") {\n";
    myfile << "m" << TableNameStr << "Repository.delete(" << tableNameStr << ");\n";
    myfile << "}\n";
    myfile << "}\n";

    myfile.close();


    this->accept();
}
