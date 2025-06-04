#pragma once
#include "FileSystemManager.h" // Make sure this path is correct
#include <msclr/marshal.h>
#include <msclr/marshal_cppstd.h>


namespace FileSystemGUI {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace msclr::interop;

    public ref class MyForm : public System::Windows::Forms::Form
    {
    public:
        MyForm(void)
        {
            InitializeComponent();
            fsManager = new FileSystemManager("NEW_FILE.txt");
            fsManager->initialize();
            UpdateFileList();
        }

    protected:
        ~MyForm()
        {
            if (components)
            {
                delete components;
            }
            //delete fsManager;
        }

    private:
        FileSystemManager* fsManager;
        System::Windows::Forms::ListBox^ listBoxFiles;
        System::Windows::Forms::TextBox^ textBoxFileName;
        System::Windows::Forms::RichTextBox^ richTextBoxContent;
        System::Windows::Forms::Button^ buttonAdd;
        System::Windows::Forms::Button^ buttonDelete;
        System::Windows::Forms::Button^ buttonModify;
        System::Windows::Forms::Button^ buttonView;
        System::Windows::Forms::Button^ buttonCopyFromWindows;
        System::Windows::Forms::Button^ buttonCopyToWindows;
        System::Windows::Forms::Label^ label1;
        System::Windows::Forms::Label^ label2;
        System::Windows::Forms::Button^ buttonClose;
        System::Windows::Forms::Button^ buttonClear;
        System::Windows::Forms::Label^ labelTitle;
        System::Windows::Forms::Label^ label3;

        System::ComponentModel::Container^ components;

        void InitializeComponent()
        {
            this->listBoxFiles = (gcnew System::Windows::Forms::ListBox());
            this->textBoxFileName = (gcnew System::Windows::Forms::TextBox());
            this->richTextBoxContent = (gcnew System::Windows::Forms::RichTextBox());
            this->buttonAdd = (gcnew System::Windows::Forms::Button());
            this->buttonDelete = (gcnew System::Windows::Forms::Button());
            this->buttonModify = (gcnew System::Windows::Forms::Button());
            this->buttonView = (gcnew System::Windows::Forms::Button());
            this->buttonCopyFromWindows = (gcnew System::Windows::Forms::Button());
            this->buttonCopyToWindows = (gcnew System::Windows::Forms::Button());
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->label2 = (gcnew System::Windows::Forms::Label());
            this->buttonClose = (gcnew System::Windows::Forms::Button());
            this->buttonClear = (gcnew System::Windows::Forms::Button());
            this->labelTitle = (gcnew System::Windows::Forms::Label());
            this->label3 = (gcnew System::Windows::Forms::Label());
            this->SuspendLayout();
            // 
            // listBoxFiles
            // 
            this->listBoxFiles->BackColor = System::Drawing::Color::Plum;
            this->listBoxFiles->Font = (gcnew System::Drawing::Font(L"Times New Roman", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->listBoxFiles->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
            this->listBoxFiles->FormattingEnabled = true;
            this->listBoxFiles->ItemHeight = 22;
            this->listBoxFiles->Location = System::Drawing::Point(47, 92);
            this->listBoxFiles->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
            this->listBoxFiles->Name = L"listBoxFiles";
            this->listBoxFiles->Size = System::Drawing::Size(298, 444);
            this->listBoxFiles->TabIndex = 0;
            // 
            // textBoxFileName
            // 
            this->textBoxFileName->BackColor = System::Drawing::Color::Plum;
            this->textBoxFileName->Font = (gcnew System::Drawing::Font(L"Times New Roman", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->textBoxFileName->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
            this->textBoxFileName->Location = System::Drawing::Point(380, 119);
            this->textBoxFileName->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
            this->textBoxFileName->Name = L"textBoxFileName";
            this->textBoxFileName->Size = System::Drawing::Size(775, 30);
            this->textBoxFileName->TabIndex = 1;
            // 
            // richTextBoxContent
            // 
            this->richTextBoxContent->BackColor = System::Drawing::Color::Plum;
            this->richTextBoxContent->Font = (gcnew System::Drawing::Font(L"Times New Roman", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->richTextBoxContent->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
            this->richTextBoxContent->Location = System::Drawing::Point(380, 185);
            this->richTextBoxContent->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
            this->richTextBoxContent->Name = L"richTextBoxContent";
            this->richTextBoxContent->Size = System::Drawing::Size(775, 306);
            this->richTextBoxContent->TabIndex = 2;
            this->richTextBoxContent->Text = L"";
            this->richTextBoxContent->TextChanged += gcnew System::EventHandler(this, &MyForm::richTextBoxContent_TextChanged);
            // 
            // buttonAdd
            // 
            this->buttonAdd->ForeColor = System::Drawing::SystemColors::ButtonFace;
            this->buttonAdd->Location = System::Drawing::Point(445, 508);
            this->buttonAdd->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
            this->buttonAdd->Name = L"buttonAdd";
            this->buttonAdd->Size = System::Drawing::Size(82, 35);
            this->buttonAdd->TabIndex = 3;
            this->buttonAdd->Text = L"Add";
            this->buttonAdd->Click += gcnew System::EventHandler(this, &MyForm::buttonAdd_Click);
            // 
            // buttonDelete
            // 
            this->buttonDelete->ForeColor = System::Drawing::SystemColors::ButtonFace;
            this->buttonDelete->Location = System::Drawing::Point(535, 508);
            this->buttonDelete->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
            this->buttonDelete->Name = L"buttonDelete";
            this->buttonDelete->Size = System::Drawing::Size(80, 35);
            this->buttonDelete->TabIndex = 4;
            this->buttonDelete->Text = L"Delete";
            this->buttonDelete->Click += gcnew System::EventHandler(this, &MyForm::buttonDelete_Click);
            // 
            // buttonModify
            // 
            this->buttonModify->ForeColor = System::Drawing::SystemColors::ButtonFace;
            this->buttonModify->Location = System::Drawing::Point(623, 508);
            this->buttonModify->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
            this->buttonModify->Name = L"buttonModify";
            this->buttonModify->Size = System::Drawing::Size(94, 35);
            this->buttonModify->TabIndex = 5;
            this->buttonModify->Text = L"Modify";
            this->buttonModify->Click += gcnew System::EventHandler(this, &MyForm::buttonModify_Click);
            // 
            // buttonView
            // 
            this->buttonView->ForeColor = System::Drawing::SystemColors::ButtonFace;
            this->buttonView->Location = System::Drawing::Point(725, 508);
            this->buttonView->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
            this->buttonView->Name = L"buttonView";
            this->buttonView->Size = System::Drawing::Size(83, 35);
            this->buttonView->TabIndex = 6;
            this->buttonView->Text = L"View";
            this->buttonView->Click += gcnew System::EventHandler(this, &MyForm::buttonView_Click);
            // 
            // buttonCopyFromWindows
            // 
            this->buttonCopyFromWindows->ForeColor = System::Drawing::SystemColors::ButtonFace;
            this->buttonCopyFromWindows->Location = System::Drawing::Point(725, 551);
            this->buttonCopyFromWindows->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
            this->buttonCopyFromWindows->Name = L"buttonCopyFromWindows";
            this->buttonCopyFromWindows->Size = System::Drawing::Size(209, 37);
            this->buttonCopyFromWindows->TabIndex = 7;
            this->buttonCopyFromWindows->Text = L"Copy from Windows";
            this->buttonCopyFromWindows->Click += gcnew System::EventHandler(this, &MyForm::buttonCopyFromWindows_Click);
            // 
            // buttonCopyToWindows
            // 
            this->buttonCopyToWindows->ForeColor = System::Drawing::SystemColors::ButtonFace;
            this->buttonCopyToWindows->Location = System::Drawing::Point(544, 551);
            this->buttonCopyToWindows->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
            this->buttonCopyToWindows->Name = L"buttonCopyToWindows";
            this->buttonCopyToWindows->Size = System::Drawing::Size(173, 37);
            this->buttonCopyToWindows->TabIndex = 8;
            this->buttonCopyToWindows->Text = L"Copy to Windows";
            this->buttonCopyToWindows->Click += gcnew System::EventHandler(this, &MyForm::buttonCopyToWindows_Click);
            // 
            // label1
            // 
            this->label1->AutoSize = true;
            this->label1->Font = (gcnew System::Drawing::Font(L"Times New Roman", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label1->ForeColor = System::Drawing::SystemColors::ButtonFace;
            this->label1->Location = System::Drawing::Point(376, 92);
            this->label1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(93, 22);
            this->label1->TabIndex = 9;
            this->label1->Text = L"File Name";
            this->label1->Click += gcnew System::EventHandler(this, &MyForm::label1_Click);
            // 
            // label2
            // 
            this->label2->AutoSize = true;
            this->label2->Font = (gcnew System::Drawing::Font(L"Times New Roman", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label2->ForeColor = System::Drawing::SystemColors::ButtonFace;
            this->label2->Location = System::Drawing::Point(376, 158);
            this->label2->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
            this->label2->Name = L"label2";
            this->label2->Size = System::Drawing::Size(70, 22);
            this->label2->TabIndex = 10;
            this->label2->Text = L"Content";
            // 
            // buttonClose
            // 
            this->buttonClose->ForeColor = System::Drawing::SystemColors::ButtonFace;
            this->buttonClose->Location = System::Drawing::Point(819, 508);
            this->buttonClose->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
            this->buttonClose->Name = L"buttonClose";
            this->buttonClose->Size = System::Drawing::Size(93, 35);
            this->buttonClose->TabIndex = 9;
            this->buttonClose->Text = L"Close";
            this->buttonClose->Click += gcnew System::EventHandler(this, &MyForm::buttonClose_Click);
            // 
            // buttonClear
            // 
            this->buttonClear->ForeColor = System::Drawing::SystemColors::ButtonFace;
            this->buttonClear->Location = System::Drawing::Point(919, 508);
            this->buttonClear->Name = L"buttonClear";
            this->buttonClear->Size = System::Drawing::Size(79, 35);
            this->buttonClear->TabIndex = 10;
            this->buttonClear->Text = L"Clear";
            this->buttonClear->Click += gcnew System::EventHandler(this, &MyForm::buttonClear_Click);
            // 
            // labelTitle
            // 
            this->labelTitle->Font = (gcnew System::Drawing::Font(L"Times New Roman", 20, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->labelTitle->ForeColor = System::Drawing::Color::Plum;
            this->labelTitle->Location = System::Drawing::Point(490, 33);
            this->labelTitle->Name = L"labelTitle";
            this->labelTitle->Size = System::Drawing::Size(123, 41);
            this->labelTitle->TabIndex = 0;
            this->labelTitle->Text = L"MTR ";
            this->labelTitle->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
            this->labelTitle->Click += gcnew System::EventHandler(this, &MyForm::labelTitle_Click);
            // 
            // label3
            // 
            this->label3->Font = (gcnew System::Drawing::Font(L"Times New Roman", 20, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label3->ForeColor = System::Drawing::SystemColors::ButtonFace;
            this->label3->Location = System::Drawing::Point(536, 33);
            this->label3->Name = L"label3";
            this->label3->Size = System::Drawing::Size(565, 41);
            this->label3->TabIndex = 11;
            this->label3->Text = L"Hard Disk Application";
            this->label3->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
            // 
            // MyForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
            this->ClientSize = System::Drawing::Size(1196, 639);
            this->Controls->Add(this->labelTitle);
            this->Controls->Add(this->label3);
            this->Controls->Add(this->label2);
            this->Controls->Add(this->label1);
            this->Controls->Add(this->buttonCopyToWindows);
            this->Controls->Add(this->buttonCopyFromWindows);
            this->Controls->Add(this->buttonView);
            this->Controls->Add(this->buttonModify);
            this->Controls->Add(this->buttonDelete);
            this->Controls->Add(this->buttonAdd);
            this->Controls->Add(this->richTextBoxContent);
            this->Controls->Add(this->textBoxFileName);
            this->Controls->Add(this->listBoxFiles);
            this->Controls->Add(this->buttonClose);
            this->Controls->Add(this->buttonClear);
            this->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
            this->Name = L"MyForm";
            this->Text = L"File System Manager";
            this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
            this->ResumeLayout(false);
            this->PerformLayout();

        }

        // Updated to work with the modified FileSystemManager
        void UpdateFileList()
        {
            listBoxFiles->Items->Clear();

            // Temporary string stream to capture printed filenames
            std::stringstream buffer;
            auto oldCout = std::cout.rdbuf(buffer.rdbuf()); // Redirect cout

            fsManager->printFileName(); // Prints filenames to cout

            std::cout.rdbuf(oldCout); // Restore cout

            // Read captured output line by line
            std::string line;
            while (std::getline(buffer, line))
            {
                if (!line.empty()) {
                    listBoxFiles->Items->Add(gcnew String(line.c_str()));
                }
            }
        }

#pragma region Button Click Events
    private:
        System::Void buttonAdd_Click(System::Object^ sender, System::EventArgs^ e)
        {
            String^ fileName = textBoxFileName->Text;
            String^ content = richTextBoxContent->Text;

            if (fileName->Length == 0)
            {
                MessageBox::Show(L"Please enter a file name.", L"Error",
                    MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            std::string stdFileName = marshal_as<std::string>(fileName);

            if (!fsManager->isFileNameUnique(stdFileName))
            {
                MessageBox::Show(L"File name already exists!",
                    L"Duplicate File",
                    MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }

            try {
                fsManager->addFileToDirectory(
                    stdFileName,
                    marshal_as<std::string>(content)
                );

                UpdateFileList();
                textBoxFileName->Clear();
                richTextBoxContent->Clear();
            }
            catch (const std::exception& ex) {
                MessageBox::Show(gcnew String(ex.what()),
                    L"Error",
                    MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }


        System::Void buttonDelete_Click(System::Object^ sender, System::EventArgs^ e)
        {
            if (listBoxFiles->SelectedIndex == -1)
            {
                MessageBox::Show(L"Please select a file.", L"Error",
                    MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            String^ fileName = listBoxFiles->SelectedItem->ToString();
            fsManager->deleteFile(marshal_as<std::string>(fileName));
            UpdateFileList();
        }

        System::Void buttonModify_Click(System::Object^ sender, System::EventArgs^ e)
        {
            if (listBoxFiles->SelectedIndex == -1)
            {
                MessageBox::Show(L"Please select a file.", L"Error",
                    MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            String^ fileName = listBoxFiles->SelectedItem->ToString();
            String^ newContent = richTextBoxContent->Text;

            fsManager->modifyFile(
                marshal_as<std::string>(fileName),
                marshal_as<std::string>(newContent)
            );

            MessageBox::Show(L"File modified successfully.",
                L"Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
        }

        System::Void buttonView_Click(System::Object^ sender, System::EventArgs^ e)
        {
            if (listBoxFiles->SelectedIndex == -1)
            {
                MessageBox::Show(L"Please select a file.", L"Error",
                    MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            String^ fileName = listBoxFiles->SelectedItem->ToString();
            std::string content = fsManager->getFileContent(marshal_as<std::string>(fileName));
            richTextBoxContent->Text = gcnew String(content.c_str());
        }

        System::Void buttonCopyFromWindows_Click(System::Object^ sender, System::EventArgs^ e)
        {
            OpenFileDialog^ openFileDialog = gcnew OpenFileDialog();
            if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
            {
                String^ filePath = openFileDialog->FileName;
                String^ fileName = System::IO::Path::GetFileName(filePath);

                try {
                    fsManager->copyFilefromWindow(
                        marshal_as<std::string>(fileName),
                        marshal_as<std::string>(System::IO::Path::GetDirectoryName(filePath))
                    );
                    UpdateFileList();
                }
                catch (const std::exception& ex) {
                    MessageBox::Show(gcnew String(ex.what()),
                        L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                }
            }
        }

        System::Void buttonCopyToWindows_Click(System::Object^ sender, System::EventArgs^ e)
        {
            if (listBoxFiles->SelectedIndex == -1)
            {
                MessageBox::Show(L"Please select a file.", L"Error",
                    MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            String^ fileName = listBoxFiles->SelectedItem->ToString();
            try {
                fsManager->copyFileToWindow(marshal_as<std::string>(fileName));
                MessageBox::Show(L"File copied to Windows successfully.",
                    L"Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
            }
            catch (const std::exception& ex) {
                MessageBox::Show(gcnew String(ex.what()),
                    L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        System::Void buttonClose_Click(System::Object^ sender, System::EventArgs^ e)
        {
            fsManager->writeToFile();
            this->Close();
        }

        System::Void buttonClear_Click(System::Object^ sender, System::EventArgs^ e)
        {
            richTextBoxContent->Clear();
        }
#pragma endregion
    private: System::Void label3_Click(System::Object^ sender, System::EventArgs^ e) {
    }
    private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
    }
    private: System::Void labelTitle_Click(System::Object^ sender, System::EventArgs^ e) {
    }
    private: System::Void richTextBoxContent_TextChanged(System::Object^ sender, System::EventArgs^ e) {
    }
    private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
    }


    };
}
