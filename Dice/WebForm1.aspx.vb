Public Class WebForm1
    Inherits System.Web.UI.Page

#Region " Web Form Designer Generated Code "

    'This call is required by the Web Form Designer.
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()

    End Sub

    'NOTE: The following placeholder declaration is required by the Web Form Designer.
    'Do not delete or move it.
    Private designerPlaceholderDeclaration As System.Object

    Private Sub Page_Init(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Init
        'CODEGEN: This method call is required by the Web Form Designer
        'Do not modify it using the code editor.
        InitializeComponent()
    End Sub

#End Region

    Private Sub Page_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load

        Dim fdCon As New Odbc.OdbcConnection("DRIVER={MySQL ODBC 3.51 Driver};SERVER=localhost; DATABASE=apba;UID=root;PASSWORD=rooster1;OPTION=3")
        Dim fdCom As New Odbc.OdbcCommand("SELECT userName FROM user", fdCon)

        fdCom.Connection.Open()

        Dim fdRead As Odbc.OdbcDataReader = fdCom.ExecuteReader(CommandBehavior.CloseConnection)

        While fdRead.Read
          
        End While

        fdCon.Close()

    End Sub

End Class
