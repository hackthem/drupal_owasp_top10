<?php
/**
* @file
* owasp_csrf.inc
*/

function owasp_csrf_form() {


    	$form = array();

	$form['credentialdetails']=array(
        '#type'=>'fieldset',
        '#title'=>t('Enter your credential details below'),
        '#description'=>t('These are all madatory')
      	);

	$form['credentialdetails']['username']=array(
            '#type'=>'textfield',
            '#title'=>t('Enter your username'),
            '#default_value'=> 'hacker',
            '#description'=>t('Your username goes here')
          );

	$form['credentialdetails']['password']=array(
            '#type'=>'password',
            '#title'=>t('Enter your password'),             
            '#description'=>t('Your password goes here')
          );

	$form['credentialdetails']['password2']=array(
            '#type'=>'password',
            '#title'=>t('Re-enter your password')
             
             
          );



    	$form['basicdetails']=array(
        '#type'=>'fieldset',
        '#title'=>t('Enter your Basic details below'),
        '#description'=>t('These are all madatory')
      	);

        $form['basicdetails']['first_name']=array(
            '#type'=>'textfield',
            '#title'=>t('Enter your first name'),
            '#default_value'=> 'hacker',
            '#description'=>t('Your first name goes here')
          );
        $form['basicdetails']['last_name']=array(
            '#type'=>'textfield',
            '#title'=>t('Enter your Last name'),
            '#default_value'=> 'hacker',
            '#description'=>t('Your Last name goes here')
          );
	$form['basicdetails']['card_number']=array(
            '#type'=>'textfield',
            '#title'=>t('Enter your Card number'),
            '#default_value'=> '0123456789',
            '#description'=>t('Your Card number goes here')
          );

          

  	$form['addressdetails']=array(
        '#type'=>'fieldset',
        '#title'=>t('Enter your Address details below'),
        '#description'=>t('These are all madatory')
      	);

	$form['addressdetails']['address']=array(
            '#type'=>'textarea',
            '#title'=>t('Enter address'),
            '#default_value'=> 'rue du hacks',
            '#description'=>t('Your Address name goes here')
          );
 
        $form['addressdetails']['city']=array(
            '#type'=>'textfield',
            '#title'=>t('Enter your city'),
            '#default_value'=> 'hackthem',
            '#description'=>t('Your city name goes here')
          );
        
	$form['addressdetails']['province']=array(
            '#type'=>'textfield',
            '#title'=>t('Enter your province'),
            '#default_value'=> 'hackthem',
            '#description'=>t('Your province goes here')
          );

	$form['addressdetails']['postcode']=array(
            '#type'=>'textfield',
            '#title'=>t('Enter your postcode'),
            '#default_value'=> '92260',
            '#description'=>t('Your postcode goes here')
          );



	    $form['submit']=array(
		'#type'=>'submit',
		'#value'=>t('Create user')
	      );

      return $form;
}


function owasp_csrf_form_submit($form, $form_state) {

	$username = $form_state['values']['username'];
     	$password = $form_state['values']['password'];
	$password2 = $form_state['values']['password2'];
	$first_name=$form_state['values']['first_name'];
	$last_name=$form_state['values']['last_name'];
	$card_number=$form_state['values']['card_number'];
	$address=$form_state['values']['address'];
	$city=$form_state['values']['city'];
	$province=$form_state['values']['province'];
	$postcode=$form_state['values']['postcode'];	


     	db_set_active('owasp');

	$query = db_query("INSERT INTO users(username,password,first_name,last_name,card_number,address,city,province,postcode) VALUES ('".$username."','".$password."','".$first_name."','".$last_name."','".$card_number."','".$address."','".$city."','".$province."','".$postcode."') ");  

 	db_set_active();



	drupal_set_message("User created");
	 
	 


}
//foncttion de validation des champs passwors
function owasp_csrf_form_validate($form, $form_state) {

	if(user_is_logged_in()){

	
	form_set_error('','You must log out first before submitting this form');
	}
 
     	$password = $form_state['values']['password'];
	$password2 = $form_state['values']['password2'];

	 
	if(empty($password))
	 	form_set_error('password', 'Password can not be empty !!!');

	if( !($password === $password2) )
		form_set_error('password2', 'Please re-enter your password !!!');

	 



}
