Imports System.Text
Imports System.IO
Imports System.Runtime.Serialization

<Serializable()> Public Class Point
    Implements IComparable

    Public x, y As Int32

    Public Sub New()
        Me.x = 0
        Me.y = 0
    End Sub

    Public Sub New(ByVal x As Int32, ByVal y As Int32)
        Me.x = x
        Me.y = y
    End Sub

    Public Overridable Function Metric() As Double
        Metric = Math.Sqrt((x ^ 2 + y ^ 2))
    End Function

    Public Overrides Function ToString() As String
        Return String.Format("({0}, {1})", x, y)
    End Function

    Public Function CompareTo(ByVal obj As Object) As Integer Implements System.IComparable.CompareTo
        Dim p As Point = CType(obj, Point)
        Return (Me.Metric() - p.Metric())
    End Function
End Class