<?php
// $Id$
function om_pssp_download_upload_file()
{
	$proposal_id = arg(4);
	$root_path = om_pssp_path();
	$query = db_select('om_pssp_proposal');
	$query->fields('om_pssp_proposal');
	$query->condition('id', $proposal_id);
	$query->range(0, 1);
	$result = $query->execute();
	$om_pssp_upload_file = $result->fetchObject();
	$samplecodename = substr($om_pssp_upload_file->samplefilepath, strrpos($om_pssp_upload_file->samplefilepath, '/') + 1);
			ob_clean();
            header("Pragma: public");
            header("Expires: 0");
            header("Cache-Control: must-revalidate, post-check=0, pre-check=0");
            header("Cache-Control: public");
            header("Content-Description: File Transfer");
            header('Content-Type: application/pdf');
            header('Content-disposition: attachment; filename="' . $samplecodename . '"');
            header('Content-Length: ' . filesize($root_path . $om_pssp_upload_file->samplefilepath));
            header("Content-Transfer-Encoding: binary");
            header('Expires: 0');
            header('Pragma: no-cache');
            readfile($root_path . $om_pssp_upload_file->samplefilepath);
	        ob_end_flush();
           	ob_clean();
           	flush();
}
function om_pssp_project_files() {
	$proposal_id = arg(4);
	$root_path = om_pssp_path();
	$query = db_select('om_pssp_submitted_abstracts_file');
	$query->fields('om_pssp_submitted_abstracts_file');
	$query->condition('proposal_id', $proposal_id);
	$query->condition('filetype', A);
	$result = $query->execute();
	$om_pssp_project_files = $result->fetchObject();
	//var_dump($om_pssp_project_files);die;
	$query1 = db_select('om_pssp_proposal');
	$query1->fields('om_pssp_proposal');
	$query1->condition('id', $proposal_id);
	$result1 = $query1->execute();
	$om_pssp = $result1->fetchObject();
	$directory_name = $om_pssp->directory_name . '/project_files/';
	$samplecodename = $om_pssp_project_files->filename;
	ob_clean();
	header("Pragma: public");
	header("Expires: 0");
	header("Cache-Control: must-revalidate, post-check=0, pre-check=0");
	header("Cache-Control: public");
	header("Content-Description: File Transfer");
	header("Content-Type: application/pdf");
	header('Content-disposition: attachment; filename="' . $samplecodename . '"');
	header("Content-Length: " . filesize($root_path . $directory_name . $samplecodename));
	header("Content-Transfer-Encoding: binary");
	header("Expires: 0");
	header("Pragma: no-cache");
	readfile($root_path . $directory_name . $samplecodename);
	ob_end_flush();
	ob_clean();
}
