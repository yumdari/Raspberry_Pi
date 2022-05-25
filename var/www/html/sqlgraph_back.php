<?php
$conn = mysqli_connect("localhost", "root", "kcci");
mysqli_set_charset($conn, "utf8");
mysqli_select_db($conn,"test");
$result = mysqli_query($conn, "select DATE, TIME, TEMPERATURE from sensing");
$data = array(array('test', '온도'));
if($result){
	while($row=mysqli_fetch_array($result))
	{
		array_push($data, array($row['DATE']."\n".$row[1], intval($row[2])));
	}
}
$options = array(
	'title' => '온도 (단위:섭씨)',
	'width' => 1000, 'height' => 500
);
?>
<script src="//www.google.com/jsapi"></script>
<script>
    let data = <?= json_encode($data) ?>;
    let options = <?= json_encode($options) ?>;
    google.load('visualization', '1.0', {'packages':['corechart']});
    google.setOnLoadCallback(function() {
        let chart = new google.visualization.ColumnChart(document.querySelector('#chart_div'));
        chart.draw(google.visualization.arrayToDataTable(data), options);
    });
</script>
<div id="chart_div"></div>
