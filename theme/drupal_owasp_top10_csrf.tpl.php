
<h3>Information</h3>
	
			<div >
				Here we have a table containing a list of users accessible to admin.
				<br>
				The admin can delete any user he wants. The aim of this demonstration is to show how an attacker 
				can force the admin to delete a specific user.
				<br>
				The attacker will inviter the admin to visit this site :<br>
				<a href="http://hackthem.free.fr/csrf_safe.php">http://hackthem.free.fr/csrf_safe.php</a>
				<br>
				The malicious code is bellow :
				<pre class="language-markup"><code><?php echo "malicous code variable" ;?></code></pre>
				Here the attack will occur because an anti-csrf token is not implemented.
			</div>
		

		
			<div > 
				<a class="accordion-toggle collapsed" data-toggle="collapse" href="#collapseOne"> HTML Code </a>
			</div>
			
				<div >
    				<pre class="language-markup"><code><?php print "HTML code" ; ?></code></pre>
				</div>  					
			
	   




			<div > 
				List of users
			</div>
			<?php if (!empty($user_id)) {?>
			<div >
    				<pre class="language-markup"><code><?php print "The user with the id=".$user_id." was deleted" ; ?></code></pre>
			</div>  
			<?php }?>
			<div >
				<table >

					<thead>
						<tr>
							<th>USER_ID</th>
							<th>USERNAME</th>
							<th>FIRST NAME</th>
							<th>LAST NAME</th>
							<th>ADDRESS</th>
						</tr>
					</thead>
					<tbody>
						<?php foreach ($users as $user): ?>
						<tr>
							<td>
								<?php print $user->user_id ; ?>
							</td>
							<td>
								<?php print $user->username ; ?>
							</td>
							<td>
								<?php print $user->first_name ;?>
							</td>
							<td>
								<?php print $user->last_name ;?>
							</td>
							<td>
								<?php print $user->address ; ?>
							</td>
							<td>
								<FORM method="GET" action="<?php echo '/owasp/CSRF/delete/user/'.$user->user_id ;?>">

									<INPUT type="hidden" name="csrf_token" value="<?php print drupal_get_token('owasp_csrf_delete_user' . $user->user_id)?>">
									<INPUT type="submit" value="delete" >
								</FORM>
							</td>
						</tr>
						<?php endforeach ?>
					</tbody>
				</table>
			</div>


	

	 



