<?php
// $Id$
function om_pssp_download_full_project()
{
	global $user;
	$id = arg(4);
	$root_path = om_pssp_path();
	//var_dump($root_path);die;
	$query = db_select('om_pssp_proposal');
	$query->fields('om_pssp_proposal');
	$query->condition('id', $id);
	$om_pssp_q = $query->execute();
	$om_pssp_data = $om_pssp_q->fetchObject();
	$PSSP_PATH = $om_pssp_data->directory_name . '/';
	/* zip filename */
	$zip_filename = $root_path . 'zip-' . time() . '-' . rand(0, 999999) . '.zip';
	/* creating zip archive on the server */
	$zip = new ZipArchive();
	$zip->open($zip_filename, ZipArchive::CREATE);
	$query = db_select('om_pssp_proposal');
	$query->fields('om_pssp_proposal');
	$query->condition('id', $id);
	$om_pssp_udc_q = $query->execute();
	$query = db_select('om_pssp_proposal');
	$query->fields('om_pssp_proposal');
	$query->condition('id', $id);
	$query = db_select('om_pssp_submitted_abstracts_file');
	$query->fields('om_pssp_submitted_abstracts_file');
	$query->condition('proposal_id', $id);
	$project_files = $query->execute();
	while ($pssp_project_files = $project_files->fetchObject()) {
		$zip->addFile($root_path . $PSSP_PATH . 'project_files/' . $pssp_project_files->filepath, $PSSP_PATH . str_replace(' ', '_', basename($pssp_project_files->filename)));
	}
	$zip_file_count = $zip->numFiles;
	//var_dump($zip_file_count);die;
	$zip->close();
	if ($zip_file_count > 0) {
		if ($user->uid) {
			/* download zip file */
			header('Content-Type: application/zip');
			header('Content-disposition: attachment; filename="' . str_replace(' ', '_', $om_pssp_data->project_title) . '.zip"');
			header('Content-Length: ' . filesize($zip_filename));
			ob_end_flush();
			ob_clean();
			flush();
			readfile($zip_filename);
			unlink($zip_filename);
		} //$user->uid
		else {
			header('Content-Type: application/zip');
			header('Content-disposition: attachment; filename="' . str_replace(' ', '_', $om_pssp_data->project_title) . '.zip"');
			header('Content-Length: ' . filesize($zip_filename));
			header("Content-Transfer-Encoding: binary");
			header('Expires: 0');
			header('Pragma: no-cache');
			ob_end_flush();
			ob_clean();
			flush();
			readfile($zip_filename);
			unlink($zip_filename);
		}
	} //$zip_file_count > 0
	else {
		drupal_set_message("There are no power system simulation project in this proposal to download", 'error');
		drupal_goto('powersystems');
	}
}
function om_pssp_download_completed_project()
{
		global $user;
	$id = arg(4);
	$root_path = om_pssp_path();
	$query = db_select('om_pssp_proposal');
	$query->fields('om_pssp_proposal');
	$query->condition('id', $id);
	$om_pssp_q = $query->execute();
	$om_pssp_data = $om_pssp_q->fetchObject();
	$PSSP_PATH = $om_pssp_data->directory_name . '/';
	/* zip filename */
	$zip_filename = $root_path . 'zip-' . time() . '-' . rand(0, 999999) . '.zip';
	/* creating zip archive on the server */
	$zip = new ZipArchive();
	$zip->open($zip_filename, ZipArchive::CREATE);
	$query = db_select('om_pssp_proposal');
	$query->fields('om_pssp_proposal');
	$query->condition('id', $id);
	$om_pssp_udc_q = $query->execute();
	$query = db_select('om_pssp_proposal');
	$query->fields('om_pssp_proposal');
	$query->condition('id', $id);
	$query = db_select('om_pssp_submitted_abstracts_file');
	$query->fields('om_pssp_submitted_abstracts_file');
	$query->condition('proposal_id', $id);
	$project_files = $query->execute();
	//var_dump($root_path . $PSSP_PATH . 'project_files/');die;
	while ($pssp_project_files = $project_files->fetchObject()) {
		$zip->addFile($root_path . $PSSP_PATH . 'project_files/' . $pssp_project_files->filepath, $PSSP_PATH . str_replace(' ', '_', basename($pssp_project_files->filename)));
	}
	$zip_file_count = $zip->numFiles;
	$zip->close();
	if ($zip_file_count > 0) {
		if ($user->uid) {
			/* download zip file */
			header('Content-Type: application/zip');
			header('Content-disposition: attachment; filename="' . str_replace(' ', '_', $om_pssp_data->project_title) . '.zip"');
			header('Content-Length: ' . filesize($zip_filename));
			ob_end_flush();
			ob_clean();
			//flush();
			readfile($zip_filename);
			unlink($zip_filename);
		} //$user->uid
		else {
			header('Content-Type: application/zip');
			header('Content-disposition: attachment; filename="' . str_replace(' ', '_', $om_pssp_data->project_title) . '.zip"');
			header('Content-Length: ' . filesize($zip_filename));
			header("Content-Transfer-Encoding: binary");
			header('Expires: 0');
			header('Pragma: no-cache');
			ob_end_flush();
			ob_clean();
			//flush();
			readfile($zip_filename);
			unlink($zip_filename);
		}
	} //$zip_file_count > 0
	else {
		drupal_set_message("There are no power system simulation project in this proposal to download", 'error');
		drupal_goto('powersystems');
	}
}